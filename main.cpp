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
    cout << "Usage: " << progname << " --client <clientID> [OPTIONS]" << endl;
    cout << "  clientID must be a number between 0 and 255." << endl;
    cout << endl;
    cout << "Possible options:" << endl;
    cout << "\t--demo\t\t\t Run program in demo mode. No oscilloscope required." << endl;
    cout << "\t--net <IP>\t\t Set the IP address for the UDP network stream." << endl;
    cout << "\t--port <port>\t\t Set the port for the UDP network stream." << endl;
    cout << "\t--osci <IP>\t\t Set the IP address for the connection to the oscilloscope." << endl;

    cout << endl;
    cout << "(c) 2012 Thomas Weininger" << endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Command line parsing
    QRegExp osciIPRegEx("^--osci$");
    QRegExp netIPRegEx("^--net$");
    QRegExp netPortRegEx("^--port$");
    QRegExp clientIDRegEx("^--client$");
    QRegExp demoModeRegEx("^--demo$");

    QRegExp numRegEx("^[0-9]{1,4}$");
    QRegExp ipRegEx("^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$");

    bool demoMode = false;
    int clientID = -1;

    QString osciip;                                                             // Default values.
    QString netip = "239.40.40.40";
    int netport = 20020;

    QStringList cmdline_args = a.arguments();

    // command line argument parsing
    for (int i = 1; i < cmdline_args.size(); i++) {                             // Eg. cmdline_args = ./app --demo 42 => size() = 3 => iterate i from 1 to size-1
        if ( demoModeRegEx.indexIn(cmdline_args.at(i)) != -1 ) {                // Do we use demo mode?
            demoMode = true;
        }
        else if ( clientIDRegEx.indexIn(cmdline_args.at(i)) != -1 ) {           // Try to get the client ID.
            if (numRegEx.indexIn(cmdline_args.at(i + 1)) != -1) {
                clientID = cmdline_args.at(++i).toInt();
            }
        }
        else if ( osciIPRegEx.indexIn(cmdline_args.at(i)) != -1 ) {
            if (ipRegEx.indexIn(cmdline_args.at(i + 1)) != -1) {
                osciip = cmdline_args.at(++i);
            }
        }
        else if ( netIPRegEx.indexIn(cmdline_args.at(i)) != -1 ) {
            if (ipRegEx.indexIn(cmdline_args.at(i++)) != -1) {
                netip = cmdline_args.at(++i);
            }
        }
        else if ( netPortRegEx.indexIn(cmdline_args.at(i)) != -1 ) {
            if (numRegEx.indexIn(cmdline_args.at(i + 1)) != -1) {
                netport = cmdline_args.at(++i).toInt();
            }
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

    SignalProcDispatcher sProc(0, osciip, netip, netport, clientID, demoMode);  // Now let's start...
    return a.exec();
}
