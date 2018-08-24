call "C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Auxiliary/Build/vcvars64.bat"
set PATH=D:/Qt/5.11.1/msvc2017_64/bin;%PATH%;
cd /D G:/QmlTest
qmake -r -tp vc "qml_test_project.pro"
cmd 

