#include "osrb_pch.h"
#include "Drops.h"

#include "imgui/imgui_addition.h"
#include "BuddyTimer.h"
#include "Utility.h"

Features::Drops::Drops(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
    m_stopWatch = std::make_unique<StopWatch>();
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
    ImGui::NewLine();


    ImGui::BeginColumns("DropsColumns", 2, ImGuiColumnsFlags_NoResize);
    {       
        ImGui::Text("Item:");
        ImGui::NextColumn();
        ImGui::Text("Amount found:");
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal | ImGuiSeparatorFlags_SpanAllColumns);
        ImGui::NextColumn();

        for (const auto& acqItem : m_acquiredItems)
        {
            ImGui::AceText(acqItem.second.ItemName);
            ImGui::NextColumn();

            ImGui::Text("%d", acqItem.second.Amount);
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
        if (pMsg->ItemInsertionType == IUT_DROP_ITEM)
        {
            auto pInvenItemInfo = OSR_API->FindItemInInventoryByUniqueNumber(pMsg->ItemGeneral.UniqueNumber);
            if (pInvenItemInfo)
            {
                uint32_t deltaAmount = pMsg->ItemGeneral.CurrentCount - pInvenItemInfo->CurrentCount;

                auto& acqItem = m_acquiredItems.find(pMsg->ItemGeneral.ItemNum);
                if (acqItem == m_acquiredItems.end()) {
                    m_acquiredItems[pMsg->ItemGeneral.ItemNum].ItemName = std::string(pInvenItemInfo->ItemInfo->ItemName);
                }
                m_acquiredItems[pMsg->ItemGeneral.ItemNum].Amount += deltaAmount;
            }   
            else
            {
                auto pServerItem = OSR_API->GetServerItemInfo(pMsg->ItemGeneral.ItemNum);
                if (pServerItem)
                {
                    auto& acqItem = m_acquiredItems.find(pMsg->ItemGeneral.ItemNum);
                    if (acqItem == m_acquiredItems.end()) {
                        m_acquiredItems[pMsg->ItemGeneral.ItemNum].ItemName = std::string(pServerItem->ItemName);
                    }
                    m_acquiredItems[pMsg->ItemGeneral.ItemNum].Amount += IS_COUNTABLE_ITEM(pServerItem->Kind) ? pMsg->ItemGeneral.CurrentCount : 1;
                }
            }
        }
        break;
    }
    case T_FC_STORE_UPDATE_ITEM_COUNT:
    case T_FC_TRADE_UPDATE_ITEM_COUNT:
    {
        MSG_FC_TRADE_UPDATE_ITEM_COUNT* pMsg = (MSG_FC_TRADE_UPDATE_ITEM_COUNT*)packet;
        if (pMsg->ItemUpdateType == IUT_DROP_ITEM)
        {
            auto pItem = OSR_API->FindItemInInventoryByUniqueNumber(pMsg->ItemUniqueNumber);
            if (pItem)
            {
                uint32_t deltaAmount = pMsg->NewCount - pItem->CurrentCount;

                auto& acqItem = m_acquiredItems.find(pItem->ItemNum);
                if (acqItem == m_acquiredItems.end()) {
                    m_acquiredItems[pItem->ItemNum].ItemName = std::string(pItem->ItemInfo->ItemName);
                }
                m_acquiredItems[pItem->ItemNum].Amount += deltaAmount;
            }
            else if(pMsg->ItemUniqueNumber == OSR_API->GetSPIUniqueNumber())
            {
                uint32_t deltaAmount = pMsg->NewCount - OSR_API->GetInventorySPI();

                auto& acqItem = m_acquiredItems.find(MONEY_ITEM_NUMBER);
                if (acqItem == m_acquiredItems.end()) {
                    m_acquiredItems[MONEY_ITEM_NUMBER].ItemName = std::string("SPI");
                }
                m_acquiredItems[MONEY_ITEM_NUMBER].Amount += deltaAmount;
            }
        }
        break;
    }
    }
}
