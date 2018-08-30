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
test_4.file = $$PWD/test_4/test_4.pro
QRunThreadTest.file = $$PWD/QRunThreadTest/QRunThreadTest.pro
buildinstall.file = $$PWD/buildinstall/buildinstall.pro

SSTDQml.file = $$PWD/SSTDQml/SSTDQml.pro

test_0.depends+=buildinstall
test_1.depends+=buildinstall
test_2.depends+=buildinstall
test_3.depends+=buildinstall
SSTDQml.depends += buildinstall
QRunThreadTest.depends+=buildinstall
test_4.depends+=buildinstall
test_4.depends+=SSTDQml

test_text_edit.file = $$PWD/test_text_edit/test_text_edit.pro
test_text_edit.depends+=buildinstall

test_text_edit1.file = $$PWD/test_text_edit1/test_text_edit1.pro
test_text_edit1.depends+=buildinstall

SUBDIRS += test_0
SUBDIRS += test_1
SUBDIRS += test_2
SUBDIRS += test_3
SUBDIRS += QRunThreadTest
SUBDIRS += buildinstall
SUBDIRS += SSTDQml
SUBDIRS += test_4
SUBDIRS += test_text_edit
SUBDIRS += test_text_edit1

