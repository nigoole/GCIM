HEADERS += \
    $$PWD/smtpmime.h \
    $$PWD/smtpclient.h \
    $$PWD/quotedprintable.h \
    $$PWD/mimetext.h \
    $$PWD/mimepart.h \
    $$PWD/mimemultipart.h \
    $$PWD/mimemessage.h \
    $$PWD/mimeinlinefile.h \
    $$PWD/mimehtml.h \
    $$PWD/mimefile.h \
    $$PWD/mimecontentformatter.h \
    $$PWD/mimeattachment.h \
    $$PWD/emailaddress.h \
    $$PWD/test/testemail.h

SOURCES += \
    $$PWD/smtpclient.cpp \
    $$PWD/quotedprintable.cpp \
    $$PWD/mimetext.cpp \
    $$PWD/mimepart.cpp \
    $$PWD/mimemultipart.cpp \
    $$PWD/mimemessage.cpp \
    $$PWD/mimeinlinefile.cpp \
    $$PWD/mimehtml.cpp \
    $$PWD/mimefile.cpp \
    $$PWD/mimecontentformatter.cpp \
    $$PWD/mimeattachment.cpp \
    $$PWD/emailaddress.cpp \
    $$PWD/test/testemail.cpp

INCLUDEPATH     += $$PWD/../emailapi
INCLUDEPATH     += $$PWD/../emailapi/test

#DEFINES         += SSL_EMAIL
