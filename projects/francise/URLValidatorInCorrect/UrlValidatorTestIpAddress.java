/* Filename: UrlValidatorTestIpAddress.java
 * Group Members: Akshay Subramanian, Edward Francis, Johannes Pikel
 * Class: CS362-400
 * Date: 2017.08.14
 * Assignment: Final Project Part B
 * Description: This file contains tests that passes IP address to
 * the isValid method of the UrlValidator.
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
public class UrlValidatorTestIpAddress extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTestIpAddress(String testName) {
      super(testName);
   }


/*************
 * First Partition - test an input below, at and above the expected upper limit of 255 for host ip addresses
 *************/
   public void testWithin255()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       assertEquals(true, urlVal.isValid("https://1.2.3.4"));
   }

   public void testAt255()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       assertEquals(true, urlVal.isValid("https://255.255.255.255"));
   }

    public void testAbove255()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(false, urlVal.isValid("https://256.256.256.256"));
    }
/*************
 * Second Partition - test inputs other than expected out of range errors to see if the problem is accepting any
 *                    host ip address or specific to range of inputs.
 *************/

    public void testBelow4()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(false, urlVal.isValid("https://1.2.3"));
    }

    public void testAt4()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(true, urlVal.isValid("https://1.2.3.4"));
    }

    public void testAbove4()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(false, urlVal.isValid("https://1.2.3.5"));
    }

/*************
 * Third Partition - test upper limit of three digit inputs and test four digit inputs
 *************/
    public void testThreeDigits()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(false, urlVal.isValid("https://999.999.999.999"));
    }

    public void testFourDigitsOne()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(false, urlVal.isValid("https://1000.1.1.1"));
    }

    public void testFourDigitsAll()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertEquals(false, urlVal.isValid("https://1000.1000.1000.1000"));
    }


}
