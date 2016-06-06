
#include <gloperate-qtquick/viewer/QmlScriptContext.h>

#include <QQmlContext>
#include <QQmlExpression>
#include <QString>
#include <QVariant>
#include <QJSValue>

#include <cppassist/logging/logging.h>

#include <cppexpose/reflection/Object.h>

#include <gloperate-qtquick/viewer/QmlEngine.h>
#include <gloperate-qtquick/viewer/QmlObjectWrapper.h>


using namespace cppassist;
using namespace cppexpose;


namespace gloperate_qtquick
{


QmlScriptContext::QmlScriptContext(QmlEngine * engine)
: m_engine(engine)
{
}

QmlScriptContext::~QmlScriptContext()
{
    // Is already done by someone else
    // Hints about identity welcome!
    //for (auto * wrappedObject : m_wrappedObjects)
    //{
        //delete wrappedObject;
    //}
}

void QmlScriptContext::initialize(cppexpose::ScriptContext * scriptContext)
{
    m_scriptContext = scriptContext;
}

void QmlScriptContext::setGlobalObject(cppexpose::PropertyGroup * obj)
{
    // Check arguments
    if (!obj) return;

    // This backend only supports the name 'gloperate' for the global object.
    // If the specified object has another name, issue a warning.
    if (obj->name() != "gloperate")
    {
        warning() << "QmlScriptContext: '" << obj->name() << "' is not supported as a name for the global scripting object. Using 'gloperate' instead.";
    }

    // Destroy former global object wrapper
    if (m_globalObjWrapper)
    {
        delete m_globalObjWrapper;
    }

    // Create object wrapper
    m_globalObjWrapper = new QmlObjectWrapper(m_engine, obj);

    // Set object as global object 'gloperate'
    m_engine->setGloperate(m_globalObjWrapper->wrapObject());
}

Variant QmlScriptContext::evaluate(const std::string & code)
{
    QQmlExpression expr(m_engine->rootContext(), nullptr, QString::fromStdString(code));

    return m_engine->fromQVariant(
        expr.evaluate()
    );
}


} // namespace gloperate_qtquick
