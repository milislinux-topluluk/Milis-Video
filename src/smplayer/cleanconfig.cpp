#include "cleanconfig.h"
#include <QFile>
#include <QDir>

void CleanConfig::clean(const QString & config_path) {
	qDebug("CleanConfig::clean");

	QStringList files_to_delete;

    QString s = config_path + "/milis_video_files.ini";
    if (QFile::exists(s)) files_to_delete << s;
	
    s = config_path + "/player_info.ini";
	if (QFile::exists(s)) files_to_delete << s;

	printf("Deleting files:\n");
	for (int n = 0; n < files_to_delete.count(); n++) {
		printf("Delete: %s\n", files_to_delete[n].toUtf8().constData());
		QFile::remove(files_to_delete[n]);
	}
}

QStringList CleanConfig::listDir(const QString &path) {
	QDir dir(path);
	QStringList file_list;

	foreach(QString file, dir.entryList(QDir::Files)) {
		file_list << QFileInfo(dir, file).absoluteFilePath();
	}

	foreach(QString sub_dir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
		file_list << listDir(path +"/"+ sub_dir);
	}

	return file_list;
}
