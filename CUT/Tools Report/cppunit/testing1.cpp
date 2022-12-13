#include <iostream>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include "server.h"
#include "client.h"

using namespace CppUnit;
using namespace std;

class TestM:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestM);
    CPPUNIT_TEST(testClientfd); 
    CPPUNIT_TEST(testSockfd);
    CPPUNIT_TEST(testCsockfd);
    CPPUNIT_TEST(testClientfdr);
    CPPUNIT_TEST(testSockfdr);
    CPPUNIT_TEST(testCsockfdr);
    CPPUNIT_TEST(testpid);
    CPPUNIT_TEST(testpidr);


    CPPUNIT_TEST_SUITE_END();

    public:
    	void setUp(void);
    	void tearDown(void);

    protected:
    	void testClientfd(void);
    	void testCsockfd(void);
	void testSockfd(void);
        void testCsockfdr(void);
	void testSockfdr(void);
        void testClientfdr(void);
	void testpid(void);
	void testpidr(void);

    private:
	Server *server;
	Client *client;
};


void TestM::testClientfd(void)
{
	CPPUNIT_ASSERT(4==server->getClientfd());
}
void TestM::testSockfd(void)
{
	CPPUNIT_ASSERT(5==server->getSockfd());
}
void TestM::testCsockfd(void)
{
	CPPUNIT_ASSERT(5==client->getClientsockfd());
}
void TestM::testClientfdr(void)
{
	CPPUNIT_ASSERT(3==server->getClientfd());
}
void TestM::testSockfdr(void)
{
	CPPUNIT_ASSERT(4==server->getSockfd());
}
void TestM::testCsockfdr(void)
{
	CPPUNIT_ASSERT(6==client->getClientsockfd());
}
void TestM::testpid(void)
{
	CPPUNIT_ASSERT(1234==client->getpid());
}
void TestM::testpidr(void)
{
	CPPUNIT_ASSERT(1233==client->getpid());
}




void TestM::setUp(void)
{
	server=new Server(4,5);
	client=new Client(5);
	client->setpid(1234);
	
}

void TestM::tearDown(void)
{
	delete server;
	delete client;
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestM );

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("PM.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}

