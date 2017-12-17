/*  smplayer, GUI front-end for mplayer.
    Copyright (C) 2006-2015 Ricardo Villalba <rvm@users.sourceforge.net>
    Copyright (C) 2013 ~ 2017 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "prefgeneral.h"
#include "../smplayer/preferences.h"
#include "../smplayer/filedialog.h"
#include "../smplayer/images.h"
#include "../smplayer/mediasettings.h"
#include "../smplayer/paths.h"
#include "../smplayer/playerid.h"
#include <QDebug>
#include "../smplayer/deviceinfo.h"

PrefGeneral::PrefGeneral(QWidget * parent, Qt::WindowFlags f)
	: PrefWidget(parent, f )
{
	setupUi(this);
	retranslateStrings();
}

PrefGeneral::~PrefGeneral()
{
}

void PrefGeneral::selectRadioButton()
{
//    QObject *obj = sender();//返回发出信号的对象，用QObject类型接收
//    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
//    QString obj_name = pbtn->objectName();
//    if(obj_name == "mplayer_radio") {
//        qDebug() << "mplayer_radio clicked......";
//    }
//    else if(obj_name == "mpv_radio") {
//        qDebug() << "mpv_radio clicked......";
//    }
}

void PrefGeneral::retranslateStrings() {
	retranslateUi(this);

    label->setStyleSheet("QLabel{background:transparent;font-size:12px;color:#999999;font-family:方正黑体_GBK;}");
    mplayer_radioButton->setObjectName("mplayer_radio");
    mplayer_radioButton->setFocusPolicy(Qt::NoFocus);
    mpv_radioButton->setObjectName("mpv_radio");
    mpv_radioButton->setFocusPolicy(Qt::NoFocus);

    pause_if_hidden_check->setFocusPolicy(Qt::NoFocus);
    preview_if_play_check->setFocusPolicy(Qt::NoFocus);

	createHelp();
}

void PrefGeneral::setData(Preferences *pref) {
    setMplayerPath(pref->mplayer_bin);
    setPauseWhenHidden(pref->pause_when_hidden);//true
    setPreviewWhenPlaying(pref->preview_when_playing);
}

void PrefGeneral::getData(Preferences * pref) {
	requires_restart = false;
	filesettings_method_changed = false;

    if (pref->mplayer_bin != mplayerPath()) {
        requires_restart = true;
        pref->mplayer_bin = mplayerPath();
        emit this->ready_to_update_driver();
        qDebug("PrefGeneral::getData: mplayer binary has changed, getting version number");
    }

    pref->pause_when_hidden = pauseWhenHidden();
    pref->preview_when_playing = previewWhenPlaying();
}

void PrefGeneral::setMplayerPath(QString path) {
    if (path == "/usr/bin/mpv") {
        mpv_radioButton->setChecked(true);
    }
    else {
        mplayer_radioButton->setChecked(true);
    }
}

QString PrefGeneral::mplayerPath() {
    if (mpv_radioButton->isChecked()) {
        return "/usr/bin/mpv";
    }
    else {
        return "/usr/bin/mplayer";
    }
}

void PrefGeneral::setPauseWhenHidden(bool b) {
    pause_if_hidden_check->setChecked(b);
}

bool PrefGeneral::pauseWhenHidden() {
    return pause_if_hidden_check->isChecked();
}

void PrefGeneral::setPreviewWhenPlaying(bool b) {
    preview_if_play_check->setChecked(b);
}

bool PrefGeneral::previewWhenPlaying() {
    return preview_if_play_check->isChecked();
}

void PrefGeneral::createHelp() {
	clearHelp();

	setWhatsThis(pause_if_hidden_check, tr("Simge durumunda duraklat"),
		tr("If this option is enabled, the file will be paused when the "
           "main window is hidden. When the window is restored, playback "
           "will be resumed."));
    setWhatsThis(preview_if_play_check, tr("Video oynatıldığında önizleme yap"),
        tr("If this option is enabled, the video preview will be displayed "
           "when the mouse is placed on the progress bar."));
    setWhatsThis(mplayer_radioButton, tr("Oynatma motoru olarak MPlayer'ı seç"),
        tr("Oynatma motorunu MPlayer'a değiştirirseniz, lütfen Milis Video'yu yeniden başlatın."));
    setWhatsThis(mpv_radioButton, tr("Oynatma motoru olarak MPV'yi seçin"),
        tr("Oynatma motorunu MPV'ye değiştirirseniz, lütfen Milis Video'yu yeniden başlatın."));
}

//#include "moc_prefgeneral.cpp"
