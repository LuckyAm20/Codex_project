#ifndef QTABLEVIEWPRINTER_H
#define QTABLEVIEWPRINTER_H

#include <QPen>
#include <QFont>
#include <QPrinter>
#include <QTableView>

class QPainter;
class QAbstractItemModel;

enum TitleFlag{
    FIRST_PAGE=0X1,
    EVERY_PAGE=0X2,
};

struct PrintColumn{
    QString name;
    int modelColumn;
    int columnWidth;
};

struct mergeColumn{
    QString text;
    QStringList columnList;
};

typedef QList<PrintColumn*> PrintColumnList;
typedef QHash<int,QList<mergeColumn*>> MergeColumnHash;



class PageTitle
{
public:
    PageTitle(QPainter *painter, QPrinter* printer);
    virtual ~PageTitle(){}
    void setPageTitle(const QString& title);
    void setTitleFont(QFont font);
    void setSideTitleFont(QFont font);
    void setSideTitle(const QStringList& sidetitle);
public:
    virtual void startDrawTitle();
private:
    QPainter* mpainter;
    QPrinter* mprinter;
    QFont titleFont;
    QFont sidetitleFont;
    QString mtitle;
    QStringList msideTitles;
};

class PageHeader
{
public:
    PageHeader(QPainter *painter);
    virtual ~PageHeader(){}
    void setPageHeaderFont(QFont font);
public:
    virtual void startDrawHeader();
private:
    QPainter* mpainter;
    QFont pageHeaderFont;
};

class PageFooter
{
public:
    PageFooter(QPainter *painter);
    ~PageFooter(){}
    virtual void startDrawFooter();
    void setCreater(const QString& name);
    void setPageFooterFont(QFont font);
    void resetPageNumber();
    void setViewFlag(bool zbr=true, bool ym=true, bool zbsj=true);
private:
    QPainter* mpainter;
    static int pageNumber;
    QString creater;
    QFont pageFooterFont;
    bool mzbr,mym, mzbsj;
};

class QTableViewPrinter
{
public:
    QTableViewPrinter(QPainter *painter, QPrinter *printer);
    bool printTable(QTableView* tableView, const QStringList &totalFields, const QStringList &visualFields);
    QString lastError();
    static int headerHeight;
    static int leftBlank;
    static int rightBlank;


    void setCellMargin(int left = 10, int right = 5, int top = 5, int bottom = 5);

    void setPageMargin(int left = 50, int right = 20, int top = 20, int bottom = 20);

    void setPen(QPen pen);

    void setHeadersFont(QFont font);

    void setContentFont(QFont font);

    void setHeaderColor(QColor color);

    void setContentColor(QColor color);

    void setTextWordWrap(Qt::TextFlag Wrap);

    void setMaxRowHeight(int height);

    void setTextAlign(Qt::AlignmentFlag align);
    void setTitleFlag(const TitleFlag type);
    void setHeaderFlag(bool flag);

    void setPagerTitle(PageTitle *pagetitle);

    void setPageHeader(PageHeader *pageheader);

    void setPagerFooter(PageFooter *pagefooter);
private:
    QPainter *painter;
    QPrinter *printer;
    PageTitle *pageTitle;
    PageHeader *pageHeader;
    PageFooter *pageFooter;
    QTableView *mTableView;
    QAbstractItemModel *model;

    int topMargin;
    int bottomMargin;
    int leftMargin;
    int rightMargin;
    int bottomHeight;
    int maxRowHeight;
    int mheaderRowHeight;

    QPen pen;
    QFont headersFont;
    QFont contentFont;
    QColor headerColor;
    QColor contentColor;
    QStringList mHeaderTitles;
    Qt::TextFlag textLineFlag;
    Qt::AlignmentFlag textAlign;
    TitleFlag titleFlag;
    PrintColumnList mColumnList;
    MergeColumnHash _mergeColumnHash;
    bool mheaderFlag;
    QString error;

private:
    //获取画笔当前位置(测试用)
    void position(const QString& str);
    //解析表格头数据(区分隐藏列,需要合并的列以及计算列宽)
    bool setPrintColumnList(const QStringList &list);
    //主体绘制方法
    bool paintTable(int row=0, int column=0, bool headFlag=false);
};
#endif // QTABLEVIEWPRINTER_H
