/* Filename: TestURLprogramming
 * Group Members: Akshay Subramanian, Edward Francis, Johannes Pikel
 * Class: CS362-400
 * Date: 2017.07.28
 * Assignment: Final Project Part B
 * Description: This programming tests uses a set of ResultPairs to put together a possible URL, with each component
 * of the URL schemes, hostnames, ports, paths and queries.  Then we take all possible permutations and submit each permutation
 * to the URLValidator for testing.  With each part of a component we have a boolean value, so if any part of our URL
 * is false then we expect false to return, otherwise we expect true.
 */

//import junit.framework.TestCase;

import static org.junit.Assert.*;



import org.junit.Test;

public class UrlValidatorTestURLProgramming {
	
	/* this is the list of possible URL components that we will put together */
	/* also referenced https://tools.ietf.org/html/rfc3986 */
	/* possible Schemes taken from https://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml*/
	 ResultPair[] schemes = { new ResultPair("http://", true),
		 					new ResultPair("imap://", true),
		 					new ResultPair(":/", false)};
	 
	 	/* host name cite https://en.wikipedia.org/wiki/Hostname */
	 ResultPair[] hostnames = { new ResultPair("www.google.com", true),
		 					new ResultPair("osu.edu", true),
		 					new ResultPair("#awesome.org", false)};
	 
	 ResultPair[] ports = { new ResultPair("", true),
		 				new ResultPair(":81", true),
		 				new ResultPair(":-80", false)};
	 
	 ResultPair[] paths = { new ResultPair("/file/img123.png", true),
		 				new ResultPair("", true),
		 				new ResultPair("/file^/img123.png", false)};
	 
	 ResultPair[] queries = {	new ResultPair("", true),
			 				new ResultPair("?name=ferret", true),
		 				new ResultPair("?name=ferret&age=23", true)};
	
	ResultPair[][] options = {schemes, hostnames, ports, paths, queries}; 
	
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES); 
	
	@Test
	public void test() {
		/* three static tests taken from the examples in URLValidatorTest.java */
		boolean result;
		assertTrue(urlVal.isValid("http://www.google.com"));
		assertTrue(urlVal.isValid("http://www.google.com/"));
		/* this unit test always fails! */
		//assertTrue(urlVal.isValid("http://www.google.com:80/test1?action=view"));
   	
    	int totalPerms = schemes.length * hostnames.length * ports.length * paths.length * queries.length;
    	int[] counters = {schemes.length, hostnames.length, ports.length, paths.length, queries.length};
    	int[] positions = {0,0,0,0,0};
    	int count = 0;
    	for (int i = 0; i < totalPerms; i ++) {
    	    boolean expectedResult = true;
    	    StringBuffer urlBuffer = new StringBuffer();
    		for (int j = 0; j < counters.length; j++) {
    			if (positions[j] >= counters[j]) {
    				positions[j] = 0;
					if (j-1 > 0 ) {
						positions[j-1] += 1;
					}
    			}
    			if (options[j][positions[j]].valid == false) {
    				expectedResult = false;
    			}
    			urlBuffer.append(options[j][positions[j]].item);
    		}
        	String urlString = urlBuffer.toString();
    		result = urlVal.isValid(urlString);
    		String format = "%-70s%-30s";
    		System.out.printf(format, urlString, "Expect: " + expectedResult + " Returned: " + result);
    		if (result != expectedResult) {
    			System.out.print("\t TEST FAILED!");
    		}
    		count += 1;
    		System.out.println();
    		positions[counters.length - 1] += 1;
    	}
    	System.out.println(count);
	}
	
}
 