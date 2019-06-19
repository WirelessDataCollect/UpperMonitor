echo on
echo Setting up environment for Qt usage...
cd /D C:\MyProgram\IDE\qt\5.8\msvc2013
cd /D F:\MyData\WirelessCollect\WiFiGui-dev\WiFiGui-dev\assistant
qhelpgenerator assistant.qhp -o assistant.qch
qcollectiongenerator assistant.qhcp -o assistant.qhc
assistant -collectionFile assistant.qhc
echo Remember to call vcvarsall.bat to complete environment setup!