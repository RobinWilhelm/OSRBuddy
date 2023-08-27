#pragma once
#include "BuddyFeatureBase.h"

#include <cstdio>

struct RARE_ITEM_INFO;
class CItemInfo;


namespace Features
{
	class TestItemUse : public BuddyFeatureBase
	{
	public:
		TestItemUse(OSRBuddyMain* buddy);
		~TestItemUse() {};

		// Geerbt über BuddyFeatureBase
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual std::string GetName() const;
		virtual FeatureType GetType() const override;

		void SaveMysterInfoToFile(FILE* fd);
		void DumpRareItemInfoToFile(FILE* fd);
		void DumpItems();

	private:
		bool m_active_switch;
	

		int m_input_itemnumber;
		CItemInfo* m_item;
		unsigned int m_item_reattack;
		bool m_item_in_lab;
		RARE_ITEM_INFO* m_rif;

		// Geerbt über BuddyFeatureBase
	};
}