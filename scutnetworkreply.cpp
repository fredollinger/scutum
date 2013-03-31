#include <QDebug>
#include <QtNetwork>
#include "scutnetworkreply.hpp"
#include "scutcommon.hpp"

namespace scutum{
ScutNetworkReply::ScutNetworkReply(QObject *parent)
    : QNetworkReply(parent)
{
}

} // namespace scutum
