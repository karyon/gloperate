
#pragma once


#include <cppexpose/reflection/Object.h>

#include <gloperate/gloperate_api.h>


namespace gloperate
{


class ViewerContext;


/**
*  @brief
*    Scripting API for system functions (loading files, exit application, ...)
*/
class GLOPERATE_API SystemApi : public cppexpose::Object
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] viewerContext
    *    Viewer context (must NOT be null!)
    */
    SystemApi(ViewerContext * viewerContext);

    /**
    *  @brief
    *    Destructor
    */
    ~SystemApi();


protected:
    // Scripting functions
    void load(const std::string & filename);
    std::string readFile(const std::string & filename);
    void writeFile(const std::string & filename, const cppexpose::Variant & value);
    void appendFile(const std::string & filename, const cppexpose::Variant & value);
    void exit(int exitCode);


protected:
    ViewerContext * m_viewerContext; ///< Viewer context (must NOT be null!)
};


} // namespace gloperate
