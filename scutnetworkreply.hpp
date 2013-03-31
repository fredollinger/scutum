#ifndef __SCUT_NETWORK_REPLY_HPP__
#define __SCUT_NETWORK_REPLY_HPP__

#include <QNetworkReply>

namespace scutum{
class ScutNetworkReply : public QNetworkReply
{
    Q_OBJECT

public:
    ScutNetworkReply(QObject *parent = 0);
};

} // namespace scutum
#endif//  __SCUT_NETWORK_REPLY_HPP__
