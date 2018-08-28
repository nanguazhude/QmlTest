#ifndef QRUNTHREADPRIVATE_HPP
#define QRUNTHREADPRIVATE_HPP

#include <QtCore/qobject.h>
#include <QtCore/qthread.h>
#include <QtCore/qvariant.h>
#include <QtCore/qpointer.h>
#include <future>
#include <atomic>

namespace sstd{

class RunEvent;

class QRunThreadCaller :public QObject {
    Q_OBJECT
public:

signals:
    void call_thread(const std::shared_ptr<RunEvent>&);
	void add_function_on_thread_destory(const std::shared_ptr<RunEvent>&);
	void quit_thread();
};

class QRunThreadRunner :public QObject {
    Q_OBJECT
public:
public slots:
    void run_thread(const std::shared_ptr<RunEvent>&);
	void add_function_on_thread_destory(const std::shared_ptr<RunEvent>&);
	void quit_thread();
public:
	std::list< QMetaObject::Connection > _m_disconnect_connets;
	std::list< std::shared_ptr<RunEvent> > _m_run_on_destory;
};

class QRunThreadThread :public QThread {
    Q_OBJECT
public:
	void run() override;
	class ConstructData {
	public:
		QRunThreadRunner * _m_Runner;
	};
	std::atomic< std::promise<ConstructData> * > _m_promise;
	~QRunThreadThread();
	QRunThreadThread();
};

class QRunThreadPrivate{
public:
    QRunThreadPrivate();
    virtual ~QRunThreadPrivate();
    QRunThreadCaller _m_caller;
	QPointer<QThread> _m_thread;
	QPointer<QRunThreadRunner> _m_runner;
};

}/*namespace sstd*/

Q_DECLARE_METATYPE(std::shared_ptr<sstd::RunEvent>)
Q_DECLARE_METATYPE(std::weak_ptr<sstd::QRunThreadPrivate>)
Q_DECLARE_METATYPE(std::shared_ptr<sstd::QRunThreadPrivate>)

#endif // QRUNTHREADPRIVATE_HPP
