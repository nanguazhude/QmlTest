#ifndef _x_QRUNTHREAD_HPP
#define _x_QRUNTHREAD_HPP

#include <memory>
#include <functional>
#include <type_traits>
#include <QtCore/qcoreevent.h>

class QThread;

namespace sstd {

class QRunThreadPrivate;

class RunEvent : public QEvent {
    using Super = QEvent;
public:
    RunEvent();
    virtual ~RunEvent();
    void run_noexcept() noexcept;
public:
    static QEvent::Type get_event_index();
protected:
    virtual void real_run() = 0;
};

class QRunThread {
public:
	QRunThread(const QRunThread &) =default;
	QRunThread(QRunThread &&) = default;
	QRunThread&operator=(const QRunThread &) = default;
	QRunThread&operator=(QRunThread &&) = default;
	virtual ~QRunThread();
public:
    QRunThread();
	QRunThread(decltype(nullptr));
public:
	static void construct();
public:
	QThread * getThread() const;
public:
	inline operator bool() const { return bool(thisp); }
	friend inline bool operator==(const QRunThread &l, const QRunThread &r) { return l.thisp == r.thisp; }
public:
	static QRunThread getRunThread(QObject *);
	void setQRunThread(QObject *);
public:
	template<typename _t_RunType>
	inline void atDestory(_t_RunType &&arg) {
		private_run<2>(std::forward<_t_RunType>(arg));
	}

	template<typename _t_RunType>
	inline void run(_t_RunType &&arg) {
		private_run<1>(std::forward<_t_RunType>(arg));
	}
private:
    void run_event(std::unique_ptr<RunEvent> &&);
	void add_run_event_on_thread_quit(std::unique_ptr<RunEvent> &&);
    std::shared_ptr<QRunThreadPrivate> thisp;
	template<int _v_Type,typename _t_RunType>
	inline void private_run(_t_RunType &&);
	static void destory_at_qapp_destory();
};

template<int _v_Type,typename _t_RunType>
inline void QRunThread::private_run(_t_RunType && argFunction){
    using FunctionType = std::remove_cv_t< std::remove_reference_t<_t_RunType>/**/>;
    class RunEventReal final : public RunEvent {
        FunctionType _m_function;
    protected:
        void real_run() override { _m_function(); }
    public:
        RunEventReal(const FunctionType & arg):_m_function(arg){}
        RunEventReal(FunctionType && arg):_m_function(std::move(arg)){}
    };
	if constexpr (_v_Type == 1) {
		this->run_event(std::make_unique<RunEventReal>(std::forward<_t_RunType>(argFunction)));
	}
	else {
		this->add_run_event_on_thread_quit(std::make_unique<RunEventReal>(std::forward<_t_RunType>(argFunction)));
	}
}

}/*namespace sstd*/

#endif // QRUNTHREAD_HPP
