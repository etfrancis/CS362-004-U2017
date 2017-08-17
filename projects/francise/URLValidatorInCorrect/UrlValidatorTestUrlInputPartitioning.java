/* Filename: TestUrlInputPartitioning.java
 * Group Members: Akshay Subramanian, Edward Francis, Johannes Pikel
 * Class: CS362-400
 * Date: 2017.08.14
 * Assignment: Final Project Part B
 * Description: This file contains some manual test examples as well as example of input partitioning
 * testing in two separate test functions.
 * 
 */
/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTestUrlInputPartitioning extends TestCase {

   //private boolean printStatus = false;
   //private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   //public void UrlValidatorTest(String testName) {
     // super(testName);
   //}

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com:1024"));
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   System.out.println(urlVal.isValid("http://www.oregonstate.edu"));
	   System.out.println(urlVal.isValid("http://www.whitehouse.gov"));
	   System.out.println(urlVal.isValid("http://www.whitehouse"));
	   System.out.println(urlVal.isValid("https://www.google.co.jp/search?q=3"));
	   System.out.println(urlVal.isValid("xyz://www.whitehouse.gov"));
	   System.out.println(urlVal.isValid("http://www. whitehouse.gov"));
	   System.out.println(urlVal.isValid("0one://www.one.com"));
	   System.out.println(urlVal.isValid("one://www.one.com:80:80"));
	   System.out.println(urlVal.isValid("one://www.one.com/one/"));
	   System.out.println(urlVal.isValid("one://www.one.com/%/"));
	   System.out.println(urlVal.isValid("http://www.amazon.com/%/"));
	   
   }
   
   String schemeValid = "http://";
   String authorityValid = "www.google.com";
   String portValid = ":80";
   String pathValid = "/path/";
   String queryValid = "?q=3";
   
   String schemeInValid = "http:////";
   String authorityInValid = " .google.com";
   String portInValid = ":-1";
   String pathInValid = "/path& /";
   String queryInValid = "?&";
   
   
   public void testPartitionTest()
   {
	   //this test partitions the input space of all into URLs into 32 divisions, based on the validity of each of 5 components that comprise the URL
	   //for example, one test case represents URLs with a valid scheme, valid authority, valid port, valid path, and valid query
	   //another test case represents URLs with valid scheme, valid authority, valid port, valid path, but invalid query
	   String schemeValid = "http://";
	   String authorityValid = "www.google.com";
	   String portValid = ":80";
	   String pathValid = "/path/";
	   String queryValid = "?q=3";
	   
	   String schemeInValid = "http:////";
	   String authorityInValid = " .google.com";
	   String portInValid = ":-1";
	   String pathInValid = "/path& /";
	   String queryInValid = "?&";
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean result = urlVal.isValid(schemeValid + authorityValid + portValid + pathValid + queryValid);
	   if(result != true)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portInValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portInValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portInValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityValid + portInValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portInValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portInValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portInValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeValid + authorityInValid + portInValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portInValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portInValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portInValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityValid + portInValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portInValid + pathValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portInValid + pathValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portInValid + pathInValid + queryInValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
	   result = urlVal.isValid(schemeInValid + authorityInValid + portInValid + pathInValid + queryValid);
	   if(result != false)
		   System.out.print("\t TEST FAILED!\n");
	   else
		   System.out.print("\t TEST PASSED!\n");
   }
 
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
