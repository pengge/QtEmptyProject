/******************************************************************************
 *
 * @file       dbutil.h
 * @brief
 * 封装了一些操作数据库的通用方法，例如插入、更新操作、查询结果返回整数、时间类型，
 * 还可以把查询结果映射成 map，甚至通过传入的映射函数把 map 映射成对象等，也就是 Bean，
 * 可以简化操作数据库的类的代码
 * @author     lzx
 * @date       2021/09/01
 *
 * @history
 *
 * 2021/09/02 lzx
 * 1.添加了事务支持，包括 transaction(),commit(),rollback();
 * 2.添加了错误信息输出 lastError()。
 *
 * 2021/09/03 lzx
 * 1.将该类静态函数改为普通函数
 * 2.直接暴露执行SQL语句的函数，和处理结果集的函数，executeSql() next() value()等。（尽量不要使用）
 * 3.添加批量执行SQL的方法。
 *****************************************************************************/

#ifndef DBUTIL_H
#define DBUTIL_H

#include <QMap>
#include <QList>
#include <QtSql>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>
#include <functional>
#include "dbutil_global.h"

class DBUTILSHARED_EXPORT DBUtil {
public:
    DBUtil();
    ~DBUtil();

    /**
     * 执行插入语句，并返回插入行的 id.
     *
     * @param sql
     * @param params
     * @return 如果执行成功返插入的记录的 id，否则返回 -1.
     */
    int insert(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 批量执行插入语句，返回执行的结果
     *
     * @param sql
     * @param params
     * @return 如果执行成功返回true，否则返回false.
     */
    bool insertBatch(const QString &sql, const QList<QVariantMap> &params = QList<QVariantMap>());

    /**
     * 执行更新语句 (update 和 delete 或者 不用返回新增ID 的 insert 语句都是更新语句).
     *
     * @param sql
     * @param params
     * @return 如没有错误返回 true， 有错误返回 false.
     */
    bool update(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 批量执行更新语句 (update 和 delete 或者 不用返回新增ID 的 insert 语句都是更新语句).
     *
     * @param sql
     * @param params
     * @return 如没有错误返回 true， 有错误返回 false.
     */
    bool updateBatch(const QString &sql, const QList<QVariantMap> &params = QList<QVariantMap>());

    /**
     * 执行查询语句，查询到一条记录，并把其映射成 map: key 是列名，value 是列值.
     *
     * @param sql
     * @param params
     * @return 返回记录映射的 map.
     */
    QVariantMap selectMap(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 执行查询语句，查询到多条记录，并把每一条记录其映射成一个 map，Key 是列名，Value 是列值.
     * 所有的 map 都放在 list 里。
     *
     * @param sql
     * @param params
     * @return 返回记录映射的 map 的 list.
     */
    QList<QVariantMap> selectMaps(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 执行查询语句，查询到一条记录，并把其映射成 map: key 是列名，value 是列值.
     *
     * @param sql
     * @param params
     * @return 返回记录映射的 map.
     */
    QVariantList selectList(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 执行查询语句，查询到多条记录，并把每一条记录其映射成一个 map，Key 是列名，Value 是列值.
     * 所有的 map 都放在 list 里。
     *
     * @param sql
     * @param params
     * @return 返回记录映射的 map 的 list.
     */
    QList<QVariantList> selectLists(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个整数值，如查询记录的个数、和等.
     *
     * @param result
     * @param sql
     * @param params
     * @return 返回 int
     */
    int selectInt(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个长整数值, 如果返回的是时间戳时很方便.
     *
     * @param result
     * @param sql
     * @param params
     * @return 返回长整数
     */
    qint64 selectInt64(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个字符串.
     * @param str
     * @param sql
     * @param params
     * @return 返回字符串
     */
    QString selectString(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是多个字符串.
     *
     * @param strs
     * @param sql
     * @param params
     * @return 返回 string list.
     */
    QStringList selectStrings(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个日期类型.
     *
     * @param date
     * @param sql
     * @param params
     * @return 返回 date
     */
    QDate selectDate(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个日期时间类型.
     *
     * @param date
     * @param sql
     * @param params
     * @return 返回 date time
     */
    QDateTime selectDateTime(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个 QVariant.
     *
     * @param str
     * @param sql
     * @param params
     * @return 返回 variant
     */
    QVariant selectVariant(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 查询结果封装成一个对象 bean.
     *
     * @param sql
     * @param params
     * @return 返回查找到的 bean, 如果没有查找到，返回 T 的默认对象，其 id 最好是 -1，这样便于有效的对象区别。
     */
    template <typename T>
    T selectBean(const QString &sql, const QVariantMap &params = QVariantMap())
    {
        T t;
        QVariantMap map = selectMap(sql, params);
        // 把 map 映射成一个 bean 对象
        QVariantMap::const_iterator iter;
        for (iter = map.begin(); iter != map.end(); ++iter)
        {
            const QVariant &value = iter.value();

            //模板函数不能使用外部的GlobalMethod::ConvertValue函数
            if(value.isNull()) {
                switch (value.type()) {
                case QMetaType::Int:
                    t.setProperty(iter.key().toLocal8Bit(), INT_NULL);
                    break;
                case QMetaType::Double:
                case QMetaType::Float:
                    t.setProperty(iter.key().toLocal8Bit(), REAL_NULL);
                    break;
                }
            }
            else {
                t.setProperty(iter.key().toLocal8Bit(), value);
            }
        }
        return t;
    }
        /**
         * 查询结果封装成一个对象 bean.
         *
         * @param sql
         * @param params
         * @param mapToBean - 把 map 映射成对象的函数.
         * @return 返回查找到的 bean, 如果没有查找到，返回 T 的默认对象，其 id 最好是 -1，这样便于有效的对象区别。
         */
        template <typename T>
        T selectBean(T mapToBean(const QVariantMap &rowMap), const QString &sql, const QVariantMap &params = QVariantMap())
        {
            // 把 map 都映射成一个 bean 对象
            return mapToBean(selectMap(sql, params));
        }

    /**
     * 执行查询语句，查询到多个结果并封装成 bean 的 list.
     *
     * @param sql
     * @param params
     * @return 返回 bean 的 list，如果没有查找到，返回空的 list.
     */
    template<typename T>
    QList<T> selectBeans(const QString &sql, const QVariantMap &params = QVariantMap())
    {
        QList<T> beans;

        // 每一个 map 都映射成一个 bean 对象
        foreach (const QVariantMap &row, selectMaps(sql, params))
        {
            T t;
            QVariantMap::const_iterator iter;
            for (iter = row.begin(); iter != row.end(); ++iter)
            {
                t.setProperty(iter.key().toLocal8Bit(), GlobalMethod::ConvertValue(iter.value()));
            }

            beans << t;
        }

        return beans;
    }


    /**
     * 执行查询语句，查询到多个结果并封装成 bean 的 list.
     *
     * @param sql
     * @param params
     * @param mapToBean - 把 map 映射成 bean 对象函数.
     * @return 返回 bean 的 list，如果没有查找到，返回空的 list.
     */
    template<typename T>
    QList<T> selectBeans(T const &mapToBean(const QVariantMap &rowMap), const QString &sql, const QVariantMap &params = QVariantMap())
    {
        QList<T> beans;

        // 每一个 map 都映射成一个 bean 对象
        foreach (const QVariantMap &row, selectMaps(sql, params)) {
            beans.append(mapToBean(row));
        }

        return beans;
    }

    /**
     * @brief 如果驱动程序支持事务，则在数据库上开始事务。
     * @return  如果操作成功则返回true，否则返回false。
     **/
    bool transaction();

    /**
     * @brief 如果驱动程序支持事务并且事务已经启动，则向数据库提交事务。
     * @return 如果操作成功则返回true，否则返回false。
     **/
    bool commit();

    /**
     * @brief 如果驱动程序支持事务并且并且事务已经启动，则回滚数据库上的事务。
     * @return 如果操作成功则返回true，否则返回false。
     **/
    bool rollback();

    /**
     * @brief 获取最后一个执行错误
     * @return
     **/
    QString lastError();

    /**
     * （公开，执行结果在外部处理）执行sql语句，执行的结果在外部使用 next() value()函数来处理。
     *
     * @param sql
     * @param params
     */
    void executeSql(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * （公开，批量执行结果在外部处理）执行sql语句，执行的结果在外部使用 next() value()函数来处理。
     *
     * @param sql
     * @param params
     */
    void executeBatchSql(const QString &sql, const QList<QVariantMap> &params = QList<QVariantMap>());

    /**
     * @brief 检索结果中的下一条记录(如果可用)，并在检索的记录上定位查询
     * @return 如果成功检索到记录，返回true,否则返回false。
     **/
    bool next();

    /**
     * @brief 返回当前记录中字段索引的值。
     * @param 字段索引
     * @return 结果值
     **/
    QVariant value(int i);

    /**
     * @brief 返回当前记录中名为name的字段的值（该重载方法效率低于 value(int i))
     * @param name
     * @return 结果值
     **/
    QVariant value(const QString &name);

    QVariantList getResultList(int size);

    QStringList getFieldNames() const;
    int getFieldSize() const;

private:
    /**
     * （私有，执行结果在内部处理）执行sql语句，执行的结果使用传进来的 Lambda 表达式处理
     *
     * @param sql
     * @param params
     * @param t - 处理 SQL 语句执行的结果的 Lambda 表达式
     */
    template <typename T>
    //    void executeSql(const QString &sql, const QVariantMap &params, std::function<void(QSqlQuery *query)> fn);
    void executeSql(const QString &sql, const QVariantMap &params, T const &t)
    {

        m_query->setForwardOnly(true);//结果集仅向前，可以更有效地利用内存，它还将提高某些数据库的性能
        m_query->prepare(sql);
        bindValues(m_query, params);

        if (m_query->exec()) {
            t(m_query);
        }
        debug(*m_query, params);
    }

    /**
     * 执行sql语句，执行的结果使用传进来的 Lambda 表达式处理
     *
     * @param sql
     * @param params
     * @param t - 处理 SQL 语句执行的结果的 Lambda 表达式
     */
    template <typename T>
    //    void executeSql(const QString &sql, const QVariantMap &params, std::function<void(QSqlQuery *query)> fn);
    void executeBatchSql(const QString &sql, const QList<QVariantMap> &params, T const &t)
    {

        m_query->setForwardOnly(true);//结果集仅向前，可以更有效地利用内存，它还将提高某些数据库的性能
        m_query->prepare(sql);
        bindBatchValues(m_query, params);

        if (m_query->execBatch()) {
            t(m_query);
        }
        debug(*m_query);
    }



    /**
     * 取得 query 的 labels (没用别名就是数据库里的列名).
     *
     * @param query
     * @return string list.
     */
    QStringList getFieldNames(const QSqlQuery &query);

    /**
     * 取得 query 的字段数量
     *
     * @param query
     * @return string list.
     */
    int getFieldSize(const QSqlQuery &query);

    /**
     * 把 map 中的 key 和 value 绑定到 query 里.
     *
     * @param query
     * @param params
     */
    void bindValues(QSqlQuery *query, const QVariantMap &params);


    /**
     * 把一批 map 中的 key 和 value 绑定到 query 里.
     *
     * @param query
     * @param params
     */
    void bindBatchValues(QSqlQuery *query, const QList<QVariantMap> &params);

    /**
     * 把 query 中的查询得到的所有行映射为 map 的 list.
     *
     * @param query
     * @return 返回 key 为列名，值为列的值的 map 的 list.
     */
    QList<QVariantMap> queryToMaps(QSqlQuery *query);

    /**
     * 把 query 中的查询得到的所有行存进二维表
     *
     * @param query
     * @return 二维表
     */
    QList<QVariantList> queryToLists(QSqlQuery *query);

    /**
     * 如果 config.json 里 database.debug 为 true，则输出执行的 SQL，如果为 false，则不输出。（输出包含参数）
     * @param query
     * @param params 需要输出的参数
     */
    void debug(const QSqlQuery &query, const QVariantMap &params);

    /**
     * 如果 config.json 里 database.debug 为 true，则输出执行的 SQL，如果为 false，则不输出.（输出不包含参数）
     * @param query
     */
    void debug(const QSqlQuery &query);

    QSqlQuery *m_query;
};

#endif // DBUTIL_H
