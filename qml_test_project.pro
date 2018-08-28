TEMPLATE = subdirs


#.subdir
#Use the specified subdirectory instead of SUBDIRS value.
#.file
#Specify the subproject pro file explicitly. Cannot be used in conjunction with .subdir modifier.
#.depends
#This subproject depends on specified subproject.
#.makefile
#The makefile of subproject. Available only on platforms that use makefiles.
#.target
#Base string used for makefile targets related to this subproject. Available only on platforms that use makefiles.

test_0.file = $$PWD/test_0/test_0.pro
test_1.file = $$PWD/test_1/test_1.pro
test_2.file = $$PWD/test_2/test_2.pro
test_3.file = $$PWD/test_3/test_3.pro
QRunThreadTest,file = $$PWD/QRunThreadTest/QRunThreadTest.pro
buildinstall.file = $$PWD/buildinstall/buildinstall.pro

test_0.depends+=buildinstall
test_1.depends+=buildinstall
test_2.depends+=buildinstall
test_3.depends+=buildinstall
QRunThreadTest.depends+=buildinstall

SUBDIRS += test_0
SUBDIRS += test_1
SUBDIRS += test_2
SUBDIRS += test_3
SUBDIRS += QRunThreadTest
SUBDIRS += buildinstall


