#include <QtCore>

#include "vxi11/vxi11_user.h"
#include "signalprocdispatcher.h"


QTextStream cin(stdin, QIODevice::ReadOnly);
QTextStream cout(stdout, QIODevice::WriteOnly);
QTextStream cerr(stderr, QIODevice::WriteOnly);

void cmdHelp(QString progname)
{
    cout << endl;
    cout << "Signal processing program for direction finding." << endl;
    cout << endl;
    cout << "Usage: " << progname << " <clientID> [OPTIONS]" << endl;
    cout << "  clientID must be a number between 0 and 255." << endl;
    cout << endl;
    cout << "Possible options:" << endl;
    cout << "\t--demo\t\t Run program in demo mode. No oscilloscope required." << endl;
    cout << endl;
    cout << "(c) 2012 Thomas Weininger" << endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Command line parsing
    QRegExp osciIPRegEx("^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$");
    QRegExp clientIDRegEx("^[0-9]{1,3}$");                                      // Matches everything from 0 to 999.
    QRegExp demoModeRegEx("--demo");
    bool demoMode = false;
    int clientID = -1;
    QString ipaddr;

    QStringList cmdline_args = a.arguments();

    // command line argument parsing
    for (int i = 1; i < cmdline_args.size(); i++) {                             // Eg. cmdline_args = ./app --demo 42 => size() = 3 => iterate i from 1 to size-1
        if ( demoModeRegEx.indexIn(cmdline_args.at(i)) != -1 )  {               // Do we use demo mode?
            demoMode = true;
        }
        else if ( clientIDRegEx.indexIn(cmdline_args.at(i)) != -1 ) {           // Try to get the client ID.
            clientID = cmdline_args.at(i).toInt();
        }
        else if ( osciIPRegEx.indexIn(cmdline_args.at(i)) != -1 ) {
            ipaddr = cmdline_args.at(i);
        }
        else {
            cerr << "Error: Unknown argument: " << cmdline_args.at(i) << endl;;
            cmdHelp(cmdline_args.at(0));
        }
    }

    if (clientID < 0 || clientID > 255) {                                       // Make sure clientID fits in the uint8_t clientID field.
        cerr << "Error: No client ID given or client ID value out of range (0 <= client ID <= 255)." << endl;
        cmdHelp(cmdline_args.at(0));
    }

    SignalProcDispatcher sProc(0, ipaddr, clientID, demoMode);                  // Now let's start...
    sProc.setup();

    return a.exec();
}
