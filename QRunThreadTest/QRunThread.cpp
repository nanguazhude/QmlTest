#include "QRunThread.hpp"
#include <QtCore/qcoreapplication.h>
#include "private/QRunThreadPrivate.hpp"
#include <list>
#include <optional>
#include <QtCore/qdebug.h>

//#define DEBUG_THREAD
#if defined(DEBUG_THREAD)

#endif

namespace {
    class QMainThreadRun : public sstd::QRunThread {
    public:
        sstd::QRunThreadRunner _m_runner;
        QMainThreadRun() :QRunThread(nullptr) {}
    };
    std::shared_ptr<sstd::QRunThread> globalCaller;
    constexpr inline const char * run_thread_property_name() { return "\xFF" "\x90" "\x12" "runthread"; }
}/*****/

sstd::QRunThread::QRunThread() {
    if (false == bool(globalCaller)) {
        /*there may be a bug!!!*/
        qDebug() << "QRunThread must run after qcoreapplication construct";
        return;
    }
    /*********************************************/
    thisp = std::make_shared<QRunThreadPrivate>();
    /*********************************************/
    auto varCaller = &(thisp->_m_caller);
    QRunThreadRunner * varRunner = nullptr;
    auto varThread = new QRunThreadThread;
    thisp->_m_thread = varThread;
    this->setQRunThread(varThread);
    varThread->moveToThread(qApp->thread());
    {QObject::connect(varThread, &QThread::finished, varThread, &QThread::deleteLater); }
    {
        std::promise<QRunThreadThread::ConstructData> varPromise;
        varThread->_m_promise.store(&varPromise);
        varThread->start();
        auto varWait = varPromise.get_future();
        auto varConstructData = varWait.get();
        varRunner = varConstructData._m_Runner;
        thisp->_m_runner = varRunner;
    }
    {varRunner->_m_disconnect_connets.push_back(QObject::connect(varCaller, &QRunThreadCaller::add_function_on_thread_destory, varRunner, &QRunThreadRunner::add_function_on_thread_destory, Qt::QueuedConnection)); }
    {varRunner->_m_disconnect_connets.push_back(QObject::connect(varCaller, &QRunThreadCaller::quit_thread, varRunner, &QRunThreadRunner::quit_thread, Qt::QueuedConnection)); }
    {varRunner->_m_disconnect_connets.push_back(QObject::connect(varCaller, &QRunThreadCaller::call_thread, varRunner, &QRunThreadRunner::run_thread, Qt::QueuedConnection)); }
    {
        QPointer<QRunThreadThread> varThreadWatcher = varThread;
        QObject::connect(qApp, &QCoreApplication::aboutToQuit, varThread, [varThreadWatcher]() {
            auto varThread = varThreadWatcher.data();
            if (varThread == nullptr) { return; }
            varThread->quit();
        }, Qt::DirectConnection);
    }
    /*********************************************/

}

sstd::QRunThreadPrivate::QRunThreadPrivate() {}

sstd::QRunThreadPrivate::~QRunThreadPrivate() {
    _m_caller.quit_thread();
}

sstd::QRunThread::~QRunThread() {}

sstd::RunEvent::RunEvent() :Super(get_event_index()) {}

sstd::RunEvent::~RunEvent() {}

void sstd::RunEvent::run_noexcept() noexcept {
    try {
        this->real_run();
    }
    catch (...) {
        /*add exception function here*/
    }
}

QEvent::Type sstd::RunEvent::get_event_index() {
    const static auto varAns = QEvent::registerEventType();
    return static_cast<QEvent::Type>(varAns);
}

void sstd::QRunThreadRunner::run_thread(const std::shared_ptr<sstd::RunEvent>&e) {
    e->run_noexcept();
}

void sstd::QRunThreadRunner::add_function_on_thread_destory(const std::shared_ptr<RunEvent>&arg) {
    _m_run_on_destory.push_back(arg);
}

void sstd::QRunThreadRunner::quit_thread() {
    auto varThread = this->thread();
    if (varThread)varThread->quit();
}

void sstd::QRunThreadThread::run() {
    /*construct the thread*/
    QRunThreadRunner varRunner;
    {
        _m_promise.load()->set_value({ &varRunner });
        _m_promise.store(nullptr);
    }
    /*run events*/
    exec();
    /*disconnet signals*/
    for (const auto & varD : varRunner._m_disconnect_connets) {
        varRunner.disconnect(varD);
    }
    /*run destroy functions*/
    for (const auto & varF : varRunner._m_run_on_destory) {
        varF->run_noexcept();
    }
}

sstd::QRunThread sstd::QRunThread::getRunThread(QObject *arg) {
    if (arg == nullptr) { return { nullptr }; }
    if (dynamic_cast<QThread *>(arg)) {
        QVariant var = arg->property(run_thread_property_name());
        if (var.isValid() == false) { return { nullptr }; }
        auto varLock = var.value<std::weak_ptr<sstd::QRunThreadPrivate>>();
        try {
            sstd::QRunThread varAns{ nullptr };
            varAns.thisp = varLock.lock();
            return std::move(varAns);
        }
        catch (...) {}
    }
    else {
        QVariant var = arg->property(run_thread_property_name());
        if (var.isValid() == false) { return { nullptr }; }
        sstd::QRunThread varAns{ nullptr };
        varAns.thisp = var.value<std::shared_ptr<sstd::QRunThreadPrivate>>();
        return std::move(varAns);
    }
    return { nullptr };
}

void sstd::QRunThread::setQRunThread(QObject *arg) {
    if (arg == nullptr) { return; }
    if (dynamic_cast<QThread *>(arg)) {
        arg->setProperty(run_thread_property_name(),
            QVariant::fromValue<std::weak_ptr<sstd::QRunThreadPrivate>>(thisp));
    }
    else {
        arg->setProperty(run_thread_property_name(),
            QVariant::fromValue<std::shared_ptr<sstd::QRunThreadPrivate>>(thisp));
    }
}

void sstd::QRunThread::destory_at_qapp_destory() {
    if (false == bool(globalCaller)) { return; }
    auto varGlobalCaller = std::move(globalCaller);
    auto varRunner = varGlobalCaller->thisp->_m_runner.data();
    if (varRunner == nullptr) { return; }
    /*disconnet signals*/
    for (const auto & varD : (*varRunner)._m_disconnect_connets) {
        (*varRunner).disconnect(varD);
    }
    /*run destroy functions*/
    for (const auto & varF : (*varRunner)._m_run_on_destory) {
        varF->run_noexcept();
    }
}
/**/

void sstd::QRunThread::construct() {

    qRemovePostRoutine(&destory_at_qapp_destory);
    qAddPostRoutine(&destory_at_qapp_destory);

    if (globalCaller) {
        globalCaller.reset();
    }

    auto varAns = std::make_shared< QMainThreadRun >();

    varAns->thisp = std::make_shared<QRunThreadPrivate>();
    varAns->setQRunThread(QThread::currentThread());

    varAns->_m_runner._m_disconnect_connets.push_back(
        QObject::connect(
            &(varAns->thisp->_m_caller), &QRunThreadCaller::call_thread,
            &(varAns->_m_runner), &QRunThreadRunner::run_thread,
            Qt::QueuedConnection));
    varAns->_m_runner._m_disconnect_connets.push_back(
        QObject::connect(
            &(varAns->thisp->_m_caller), &QRunThreadCaller::add_function_on_thread_destory,
            &(varAns->_m_runner), &QRunThreadRunner::add_function_on_thread_destory,
            Qt::QueuedConnection));

    varAns->thisp->_m_runner = &(varAns->_m_runner);
    varAns->thisp->_m_thread = QThread::currentThread();

    globalCaller = std::move(varAns);
}

QThread * sstd::QRunThread::getThread() const {
    if (thisp) {
        return thisp->_m_thread.data();
    }
    else if (globalCaller) {
        return globalCaller->thisp->_m_thread.data();
    }
    return nullptr;
}

sstd::QRunThreadThread::~QRunThreadThread() {
#if defined(DEBUG_THREAD)
    qDebug() << "thread destoryed!";
#endif

}
sstd::QRunThreadThread::QRunThreadThread() {}

void sstd::QRunThread::add_run_event_on_thread_quit(std::unique_ptr<RunEvent> && arg) {
    if (thisp) {
        if (thisp->_m_runner) {
            thisp->_m_caller.add_function_on_thread_destory(std::move(arg));
        }
    }
    else if (globalCaller) {
        globalCaller->thisp->_m_caller.add_function_on_thread_destory(std::move(arg));
    }
}

void sstd::QRunThread::run_event(std::unique_ptr<RunEvent> && arg) {
    if (thisp) {
        if (thisp->_m_runner) {
            thisp->_m_caller.call_thread(std::move(arg));
        }
    }
    else if (globalCaller) {
        globalCaller->thisp->_m_caller.call_thread(std::move(arg));
    }
}

sstd::QRunThread::QRunThread(decltype(nullptr)) {
    if (globalCaller) { thisp = globalCaller->thisp; }
}

void sstd::QRunThread::add_child(const QRunThread &arg) {
    if (thisp) {
        if (arg.thisp == thisp) { return; }
        if (globalCaller) {
            if (globalCaller->thisp == thisp) { return; }
        }
        thisp->_m_children.insert(arg);
    }
}

void sstd::QRunThread::remvoe_child(const QRunThread &arg) {
    if (thisp) {
        thisp->_m_children.erase(arg);
    }
}

