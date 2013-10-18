#include "drawoptions.h"

using namespace MyPattern::Base;

DrawOptions::DrawOptions()
{
}


void DrawOptions::set_paper_settings(const PaperSettings& paper_settings)
{
    this->m_paperSettings = paper_settings;
}

PaperSettings DrawOptions::get_paper_settings()
{
    return this->m_paperSettings;
}
