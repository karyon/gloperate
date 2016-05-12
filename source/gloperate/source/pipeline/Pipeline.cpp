
#include <gloperate/pipeline/Pipeline.h>


namespace gloperate
{


Pipeline::Pipeline(ViewerContext * viewerContext, const std::string & name, Pipeline * parent)
: Stage(viewerContext, name, parent)
{
}

Pipeline::~Pipeline()
{
}

const std::vector<Stage *> Pipeline::stages() const
{
    return m_stages;
}

void Pipeline::registerStage(Stage * stage)
{
    if (!stage)
    {
        return;
    }

    m_stages.push_back(stage);
}


} // namespace gloperate
