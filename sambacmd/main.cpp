#include "sambacore.h"

#include <QCoreApplication>
#include <QTimer>
#include <QUrl>
#include <stdio.h>
#include <stdlib.h>

Q_LOGGING_CATEGORY(sambaLogCmd, "samba.cmd")

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QCoreApplication::setApplicationName("sambacmd");
	QCoreApplication::setApplicationVersion("3.0-pre3");

	QLoggingCategory::setFilterRules("*.debug=false\n"
									 "qml.debug=true");
	qSetMessagePattern("%{message}");

	QCommandLineParser parser;
	parser.setApplicationDescription("SAM-BA Command Line Tool");
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption scriptOption("x",
			QCoreApplication::translate("main", "Execute script <script-file>."),
			QCoreApplication::translate("main", "script-file"));
	parser.addOption(scriptOption);
	parser.process(app);

	QString script = parser.value(scriptOption);
	if (script.isEmpty())
	{
		fprintf(stderr, parser.helpText().toLocal8Bit().constData());
		return -1;
	}

	SambaCore core(&app);

	qCDebug(sambaLogCmd, "Loading script from %s", script.toLatin1().constData());
	core.evaluateScript(QUrl::fromLocalFile(script));

	//return app.exec();
}
