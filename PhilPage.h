#ifndef PHILPAGE_H
#define PHILPAGE_H

#include <QObject>
#include <QWidget>

class PhilView;
class PhilThread;

class PhilPage : public QWidget
{
    Q_OBJECT

template<typename T> using unique_ptr = std::unique_ptr<T>;

//---------------------------------------- Fields
private:
    static const size_t PHILS_COUNT = 4;

    //todo remove raw pointers
    QWidget* forks [PHILS_COUNT];
    PhilView* philViews [PHILS_COUNT];
    PhilThread* philThreads[PHILS_COUNT];

//---------------------------------------- Methods
public:
    explicit PhilPage(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

signals:

private slots:
    void SlotOnStartButtonPressed();
};

#endif // PHILPAGE_H
