/* Filename: TestManual
 * Group Members: Akshay Subramanian, Edward Francis, Johannes Pikel
 * Class: CS362-400
 * Date: 2017.07.28
 * Assignment: Final Project Part B
 * Description: perform manual testing of various URLs to the isVAlid method.
 * */

import static org.junit.Assert.*;

import org.junit.Test;

public class UrlValidatorTestManual {

	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	public void printfail(boolean result, boolean expected, String url) {
		String format = "%-50s%-30s";                                                              
		System.out.printf(format, url, "Expect: " + expected + " Returned: " + result); 
		System.out.print("\t TEST FAILED!");                                                                                                                                          
		System.out.println();                                                                      
	
	}
	
	public void printsuccess(boolean result, boolean expected, String url) {
		String format = "%-50s%-30s";                                                              
		System.out.printf(format, url, "Expect: " + expected + " Returned: " + result);                                                         
		System.out.print("\t TEST PASSED!");                                                                                                                                          
		System.out.println();
	}

	public void picker(boolean a, boolean b, String url) {
		if (a == b) {
			printsuccess(a, b, url);
		} else {
			printfail(a, b, url);
		}
	}
	
	@Test
	public void test() {
		boolean result;
		String url;
		/* two static unit tests just to make sure everything is working correctly */
		//assertTrue(urlVal.isValid("http://www.google.com"));
		//assertTrue(urlVal.isValid("http://www.google.com/"));
		
		//test the first branch with a null
		picker(urlVal.isValid(null), false, "Null passed in");
		//then test with just a space
		url = " ";
		picker(urlVal.isValid(url), false, "Just a space");
		url = "()";
		picker(urlVal.isValid(url), false, url);
		url = ":/";
		picker(urlVal.isValid(url), false, url);
		url = "http://";
		picker(urlVal.isValid(url), false, url);
		url = "http://http://";
		picker(urlVal.isValid(url), false, url);
		url = "file:/";
		picker(urlVal.isValid(url), false, url);
		url = "file:///foo.txt";
		picker(urlVal.isValid(url), true, url);
		url = "file:///";
		picker(urlVal.isValid(url), true, url);
		url = "file:///www.google.com";
		picker(urlVal.isValid(url), true, url);
		url = "http://www.google.com:1024";
		picker(urlVal.isValid(url), true, url);
		url = "http://www.google.com:999";
		picker(urlVal.isValid(url), true, url);
		url = "http://www.google.com:10240";
		picker(urlVal.isValid(url), true, url);
		url = "http://www.google.com";
		picker(urlVal.isValid(url), true, url);
		url = "http://google.com";
		picker(urlVal.isValid(url), true, url);
		url += "/../";
		picker(urlVal.isValid(url), false, url);
		url = "http://google.com?foo=bar";
		picker(urlVal.isValid(url), true, url);
		url = "http://www.google.sing/#/aa/?!?../?boo=bar";
		picker(urlVal.isValid(url), false, url);
		url = "http://google.com/%/";
		picker(urlVal.isValid(url), false, url);
		
		
		
	}
	

}
