#include "osrb_pch.h"
#include "Drops.h"

#include "imgui/imgui_addition.h"
#include "BuddyTimer.h"
#include "Utility.h"

Features::Drops::Drops(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
    m_stopWatch = std::make_unique<StopWatch>();

    for(int i = 0; i < sizeof(m_DropsFilter); i++)
        m_DropsFilter[i] = false;

    m_DropsFilter[IUT_DROP_ITEM] = true;
}

Features::Drops::~Drops()
{
}

Features::FeatureType Features::Drops::GetType() const
{
    return Features::FeatureType::Drops;
}

std::string Features::Drops::GetName() const
{
    return "Drops";
}

void Features::Drops::Tick()
{
}

void Features::Drops::RenderImGui()
{
    if (ImGui::Button("Start"))
    {
        Enable(true);
        m_stopWatch->Start();
    }
    ImGui::SameLine();

    if (ImGui::Button("Stop"))
    {
        Enable(false);
        m_stopWatch->Stop();
    }
    ImGui::SameLine();

    ImGui::AceText((IsEnabled()) ? "\\gStarted" : "\\rStopped");


    ImGui::Text("Collection Time: %s", Utility::GetTimeString(m_stopWatch->GetElapsedTime()).c_str());
    ImGui::SameLine();
     
    if (ImGui::Button("Reset")) 
    {
        m_acquiredItems.clear();
        m_stopWatch->Reset();
    }

    if (ImGui::CollapsingHeader("Filter", ImGuiTreeNodeFlags_Framed))
    {
        ImGui::BeginColumns("DropsFilterColumns", 4, ImGuiColumnsFlags_NoResize);
        {
            ImGui::Checkbox("General", &m_DropsFilter[IUT_GENERAL]);
            ImGui::Checkbox("Drop", &m_DropsFilter[IUT_DROP_ITEM]);
            ImGui::Checkbox("Mixing", &m_DropsFilter[IUT_MIXING]);
            ImGui::Checkbox("Trade", &m_DropsFilter[IUT_TRADE]);
            ImGui::Checkbox("Shop", &m_DropsFilter[IUT_SHOP]);
            ImGui::Checkbox("Quest", &m_DropsFilter[IUT_QUEST]);
            ImGui::Checkbox("Admin", &m_DropsFilter[IUT_ADMIN]);
            ImGui::Checkbox("Bullet", &m_DropsFilter[IUT_BULLET]);
            ImGui::Checkbox("Skill", &m_DropsFilter[IUT_SKILL]);        
            ImGui::NextColumn();

            ImGui::Checkbox("Loading", &m_DropsFilter[IUT_LOADING]);
            ImGui::Checkbox("Auction", &m_DropsFilter[IUT_AUCTION]);
            ImGui::Checkbox("Enchant", &m_DropsFilter[IUT_ENCHANT]);
            ImGui::Checkbox("Use Item", &m_DropsFilter[IUT_USE_ITEM]);
            ImGui::Checkbox("Mgame Event", &m_DropsFilter[IUT_MGAME_EVENT]);
            ImGui::Checkbox("Use Energy", &m_DropsFilter[IUT_USE_ENERGY]);
            ImGui::Checkbox("Expire Card Item", &m_DropsFilter[IUT_EXPIRE_CARD_ITEM]);
            ImGui::Checkbox("Penalty On Dead", &m_DropsFilter[IUT_PENALTY_ON_DEAD]);
            ImGui::Checkbox("Penalty Agear Fuel Allin", &m_DropsFilter[IUT_PENALTY_AGEAR_FUEL_ALLIN]);
            ImGui::NextColumn(); 

            ImGui::Checkbox("Influencewar Killer Bonus", &m_DropsFilter[IUT_INFLUENCEWAR_KILLER_BONUS]);
            ImGui::Checkbox("Bonus Item", &m_DropsFilter[IUT_BONUS_ITEM]);
            ImGui::Checkbox("Bazaar Sell", &m_DropsFilter[IUT_BAZAAR_SELL]);
            ImGui::Checkbox("Bazaar Buy", &m_DropsFilter[IUT_BAZAAR_BUY]);
            ImGui::Checkbox("Randombox", &m_DropsFilter[IUT_RANDOMBOX]);
            ImGui::Checkbox("Give Event Item", &m_DropsFilter[IUT_GIVEEVENTITEM]);
            ImGui::Checkbox("Guild Store", &m_DropsFilter[IUT_GUILD_STORE]);
            ImGui::Checkbox("Expire Item", &m_DropsFilter[IUT_EXPIRE_ITEM]);
            ImGui::Checkbox("Store", &m_DropsFilter[IUT_STORE]);
            ImGui::NextColumn();

            ImGui::Checkbox("Store Fee", &m_DropsFilter[IUT_STORE_FEE]);
            ImGui::Checkbox("Arena Item", &m_DropsFilter[IUT_ARENA_ITEM]);
            ImGui::Checkbox("Turorial Pay Item", &m_DropsFilter[IUT_TUTORIAL_PAY_ITEM]);
            ImGui::Checkbox("Expediencyfund Payback", &m_DropsFilter[IUT_EXPEDIENCYFUND_PAYBACK]);
            ImGui::Checkbox("Give Event Item Couponevent", &m_DropsFilter[IUT_GIVEEVENTITEM_COUPONEVENT]);
            ImGui::Checkbox("Lucky Item", &m_DropsFilter[IUT_LUCKY_ITEM]);
            ImGui::Checkbox("War Contribution", &m_DropsFilter[IUT_WAR_CONTRIBUTION]);
            ImGui::Checkbox("War Contribution Leader", &m_DropsFilter[IUT_WAR_CONTRIBUTION_LEADER]);
            ImGui::Checkbox("War Contribution Guild", &m_DropsFilter[IUT_WAR_CONTRIBUTION_GUILD]);
            ImGui::Checkbox("Dissolution Item", &m_DropsFilter[IUT_DISSOLUTION_ITEM]); // doesn exist in osr
        }
        ImGui::EndColumns();
    }
    ImGui::NewLine();

    ImGui::BeginColumns("DropsColumns", 4, ImGuiColumnsFlags_NoResize);
    {       
        ImGui::Text("Item:");
        ImGui::NextColumn();
        ImGui::Text("Amount changed:");
        ImGui::NextColumn();
        ImGui::Text("Item:");
        ImGui::NextColumn();
        ImGui::Text("Amount changed:");

        ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal | ImGuiSeparatorFlags_SpanAllColumns);
        ImGui::NextColumn();

        for (const auto& acqItem : m_acquiredItems)
        {
            int DeltaAmount = 0;
            for (const auto& acqItemDetail : acqItem.second)
            {
                if (m_DropsFilter[acqItemDetail.first]) {
                    DeltaAmount += acqItemDetail.second.DeltaAmount;                     
                }
            }

            if (DeltaAmount == 0)
                continue;

            ImGui::AceText(acqItem.second.begin()->second.ItemName);
            ImGui::NextColumn();

            ImGui::Text("%d", DeltaAmount);
            ImGui::NextColumn();
        }
    }
    ImGui::EndColumns();
}



bool Features::Drops::OnReadPacket(unsigned short msgtype, byte* packet)
{
    if (IsEnabled() == false)
        return false;

    switch (msgtype)
    {
    case T_FC_STORE_INSERT_ITEM:
    case T_FC_TRADE_INSERT_ITEM:
    {   
        MSG_FC_TRADE_INSERT_ITEM* pMsg = (MSG_FC_TRADE_INSERT_ITEM*)packet;
        auto pInvenItemInfo = OSR_API->FindItemInInventoryByUniqueNumber(pMsg->ItemGeneral.UniqueNumber);
        if (pInvenItemInfo)
        {
            uint32_t deltaAmount = pMsg->ItemGeneral.CurrentCount - pInvenItemInfo->CurrentCount;

            auto& acqItem = m_acquiredItems.find(pMsg->ItemGeneral.ItemNum);
            if (acqItem == m_acquiredItems.end()) {
                m_acquiredItems[pMsg->ItemGeneral.ItemNum][pMsg->ItemInsertionType].ItemName = std::string(pInvenItemInfo->ItemInfo->ItemName);
            }
            m_acquiredItems[pMsg->ItemGeneral.ItemNum][pMsg->ItemInsertionType].DeltaAmount += deltaAmount;
        }   
        else
        {
            auto pServerItem = OSR_API->GetServerItemInfo(pMsg->ItemGeneral.ItemNum);
            if (pServerItem)
            {
                auto& acqItem = m_acquiredItems.find(pMsg->ItemGeneral.ItemNum);
                if (acqItem == m_acquiredItems.end()) {
                    m_acquiredItems[pMsg->ItemGeneral.ItemNum][pMsg->ItemInsertionType].ItemName = std::string(pServerItem->ItemName);
                }
                m_acquiredItems[pMsg->ItemGeneral.ItemNum][pMsg->ItemInsertionType].DeltaAmount += IS_COUNTABLE_ITEM(pServerItem->Kind) ? pMsg->ItemGeneral.CurrentCount : 1;
            }
        }
        break;
    }
    case T_FC_STORE_UPDATE_ITEM_COUNT:
    case T_FC_TRADE_UPDATE_ITEM_COUNT:
    {
        MSG_FC_TRADE_UPDATE_ITEM_COUNT* pMsg = (MSG_FC_TRADE_UPDATE_ITEM_COUNT*)packet;     
        auto pItem = OSR_API->FindItemInInventoryByUniqueNumber(pMsg->ItemUniqueNumber);
        if (pItem)
        {
            uint32_t deltaAmount = pMsg->NewCount - pItem->CurrentCount;

            auto& acqItem = m_acquiredItems.find(pItem->ItemNum);
            if (acqItem == m_acquiredItems.end()) {
                m_acquiredItems[pItem->ItemNum][pMsg->ItemUpdateType].ItemName = std::string(pItem->ItemInfo->ItemName);
            }
            m_acquiredItems[pItem->ItemNum][pMsg->ItemUpdateType].DeltaAmount += deltaAmount;
        }
        else if(pMsg->ItemUniqueNumber == OSR_API->GetSPIUniqueNumber())
        {
            uint32_t deltaAmount = pMsg->NewCount - OSR_API->GetInventorySPI();

            auto& acqItem = m_acquiredItems.find(MONEY_ITEM_NUMBER);
            if (acqItem == m_acquiredItems.end()) {
                m_acquiredItems[MONEY_ITEM_NUMBER][pMsg->ItemUpdateType].ItemName = std::string("SPI");
            }
            m_acquiredItems[MONEY_ITEM_NUMBER][pMsg->ItemUpdateType].DeltaAmount += deltaAmount;
        }
        break;
    }
    }
}
