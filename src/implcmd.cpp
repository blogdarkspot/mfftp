#include "implcmd.h"
#include <windows.h>

namespace FTP {
namespace CMD {

    /**
     *  USER NAME (USER)

            The argument field is a Telnet string identifying the user.
            The user identification is that which is required by the
            server for access to its file system.  This command will
            normally be the first command transmitted by the user after
            the control connections are made (some servers may require
            this).  Additional identification information in the form of
            a password and/or an account command may also be required by
            some servers.  Servers may allow a new USER command to be
            entered at any point in order to change the access control
            and/or accounting information.  This has the effect of
            flushing any user, password, and account information already
            supplied and beginning the login sequence again.  All
            transfer parameters are unchanged and any file transfer in
            progress is completed under the old access control
            parameters. 

            USER
                  230
                  530
                  500, 501, 421
                  331, 332
            **/
    bool User(const char* accountUserName)
    {
        char domain[256];
        BYTE sid[SECURITY_MAX_SID_SIZE];
        DWORD cbSid = SECURITY_MAX_SID_SIZE, cbDomain = 256;
        SID_NAME_USE snu = SidTypeInvalid;

        BOOL bRet = LookupAccountName(NULL, accountUserName, sid, &cbSid, domain, &cbDomain, &snu);

        return bRet ? true : false;
    }

    /**
     * The argument field is a Telnet string specifying the user's
            password.  This command must be immediately preceded by the
            user name command, and, for some sites, completes the user's
            identification for access control.  Since password
            information is quite sensitive, it is desirable in general
            to "mask" it or suppress typeout.  It appears that the
            server has no foolproof way to achieve this.  It is
            therefore the responsibility of the user-FTP process to hide
            the sensitive password information.
            PASS
                  230
                  202
                  530
                  500, 501, 503, 421
                  332
            **/
    bool Pass(const char* accountUserName, const char* password)
    {
        bool ret = false;
        BOOL bLoggedOn = FALSE;
        HANDLE hToken = NULL;

        bLoggedOn = LogonUser(accountUserName, NULL, password, LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken);

        if (bLoggedOn && ImpersonateLoggedOnUser(hToken)) {
            ret = true;
        }

        return ret;
    }

    /**
     *  This command terminates a USER and if file transfer is not
            in progress, the server closes the control connection.  If
            file transfer is in progress, the connection will remain
            open for result response and the server will then close it.
            If the user-process is transferring files for several USERs
            but does not wish to close and then reopen connections for
            each, then the REIN command should be used instead of QUIT.

            An unexpected close on the control connection will cause the
            server to take the effective action of an abort (ABOR) and a
            logout (QUIT).
            **/
    bool Quit()
    {
        RevertToSelf();
        return true;
    }

    /**
     * 
     *  The argument is a HOST-PORT specification for the data port
            to be used in data connection.  There are defaults for both
            the user and server data ports, and under normal
            circumstances this command and its reply are not needed.  If
            this command is used, the argument is the concatenation of a
            32-bit internet host address and a 16-bit TCP port address.
            This address information is broken into 8-bit fields and the
            value of each field is transmitted as a decimal number (in
            character string representation).  The fields are separated
            by commas.  A port command would be:

               PORT h1,h2,h3,h4,p1,p2

            where h1 is the high order 8 bits of the internet host
            address.
            */
    bool Port()
    {
        return true;
    }

    /**
     * The argument specifies the representation type as described
            in the Section on Data Representation and Storage.  Several
            types take a second parameter.  The first parameter is
            denoted by a single Telnet character, as is the second
            Format parameter for ASCII and EBCDIC; the second parameter
            for local byte is a decimal integer to indicate Bytesize.
            The parameters are separated by a <SP> (Space, ASCII code
            32).

            The following codes are assigned for type:

                         \    /
               A - ASCII |    | N - Non-print
                         |-><-| T - Telnet format effectors
               E - EBCDIC|    | C - Carriage Control (ASA)
                         /    \
               I - Image

               L <byte size> - Local byte Byte size
                The default representation type is ASCII Non-print.  If the
            Format parameter is changed, and later just the first
            argument is changed, Format then returns to the Non-print
            default.
            */
    bool Type()
    {
        return true;
    }

    /**
     * The argument is a single Telnet character code specifying
            the data transfer modes described in the Section on
            Transmission Modes.

            The following codes are assigned for transfer modes:

               S - Stream
               B - Block
               C - Compressed

            The default transfer mode is Stream.
            */
    bool Mode()
    {
        return true;
    }

    /**
     * The argument is a single Telnet character code specifying
            file structure described in the Section on Data
            Representation and Storage.

            The following codes are assigned for structure:

               F - File (no record structure)
               R - Record structure
               P - Page structure

            The default structure is File.
            */
    bool STUR()
    {
        return true;
    }

    /**
     *  This command causes the server-DTP to transfer a copy of the
            file, specified in the pathname, to the server- or user-DTP
            at the other end of the data connection.  The status and
            contents of the file at the server site shall be unaffected.
            */
    bool RETR()
    {
        return true;
    }

    /**
     * This command causes the server-DTP to accept the data
            transferred via the data connection and to store the data as
            a file at the server site.  If the file specified in the
            pathname exists at the server site, then its contents shall
            be replaced by the data being transferred.  A new file is
            created at the server site if the file specified in the
            pathname does not already exist.*/
    bool STRO()
    {
        return true;
    }

    /**
     *     NOOP (NOOP)

            This command does not affect any parameters or previously
            entered commands. It specifies no action other than that the
            server send an OK reply

    */
    bool NOOP()
    {
        return true;
    }
};
};