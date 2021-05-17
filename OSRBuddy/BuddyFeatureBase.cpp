#include "BuddyFeatureBase.h"
#include "imgui/imgui_addition.h"

void BuddyFeatureBase::Enable(bool enable)
{
	if (m_enabled == enable) {
		return;
	}

	if (m_enabled)
	{
		m_enabled = false;
		OnDisable();
	}
	else
	{
		m_enabled = true;
		OnEnable();
	}
}	 

bool BuddyFeatureBase::DrawEnableCheckBox()
{
	bool enable = m_enabled;
	if (ImGui::FancyCheckbox("Enable", &enable)) {
		Enable(enable);
	}
	return enable;
}
