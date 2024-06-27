#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QThread>
#include <QSettings>
#include <windows.h>

//监听系统主题子线程
class ListeningSystemTheme final : public QThread
{
private:
    friend class Theme;
    explicit ListeningSystemTheme(QObject *parent = nullptr);
    void stop();
    HKEY reg = NULL;                // 注册表项句柄
    HANDLE hEventArray[2] = {NULL}; // 事件对象数组
protected:
    void run() override;
};


//使用单例模式
class Theme final : public QObject
{
    Q_OBJECT
private:
    explicit Theme(QObject *parent = nullptr);

public:
    ~Theme();
    enum class Type
    {
        LIGHT,
        DARK
    };
    static Theme::Type themeType();
    static Theme *themeObject();
    static bool isLigth();
    static bool isDark();
public slots:
    static void setTheme(Theme::Type themeType);
    static void toggleLight();  // 切换浅色
    static void toggleDark();   // 切换深色
    static void followSystem(); // 跟随系统
    static void toggleTheme();  // 切换主题
    static bool isFollowSystem();

private:
    static Type type;
    static bool is_follow_system;
    ListeningSystemTheme *L;
signals:
    void themeChange(Theme::Type);
};

#endif // THEME_H
