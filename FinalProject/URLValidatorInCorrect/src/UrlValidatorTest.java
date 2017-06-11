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
/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest {

    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

    public UrlValidatorTest(String testName) {}

    /**
     * Tests various specific cases manually
     */
    public void testManualTest() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        printHeader("isValid manually");

        System.out.println(String.format("Testing valid urls..."));
        testIsValid("http://foo.com/bar", "", "", true);
        testIsValid("https://foo.com/bar", "", "", true);
        testIsValid("file:///foo", "", "", true);
        testIsValid("http://foo.ru/bar", "", "", true);
        testIsValid("http://foo.com?q=bar", "", "", true);
        testIsValid("http://foo.com:8080", "", "", true);
        System.out.println(String.format("Done testing valid urls.\n"));

        System.out.println(String.format("Testing valid urls..."));
        testIsValid("http://123.456.789.000", "", "", false);
        testIsValid("http:/foo.com", "", "", false);
        testIsValid("http://foo.com/../", "", "", false);
        System.out.println(String.format("Done testing valid urls.\n"));
    }

    /**
     * Tests all valid sections of url
     */
    public void testYourFirstPartition() {
        String none = "";
        String http = "http://";
        String google = "www.google.com";
        String url = http + google;

        printHeader("isValid with valid URLs");
        testSection(validSchemes, "Valid Scheme", none, google, true);
        testSection(validHosts, "Valid Host", http, none, true);
        testSection(validPorts, "Valid Port", url, none, true);
        testSection(validPaths, "Valid Path", url, none, true);
        testSection(validQuerys, "Valid Query", url, none, true);
    }

    /**
     * Tests all invalid sections of url
     */
    public void testYourSecondPartition() {
        String none = "";
        String http = "http://";
        String google = "www.google.com";
        String url = http + google;

        printHeader("isValid with invalid URLs");
        testSection(invalidSchemes, "Invalid Scheme", none, google, false);
        testSection(invalidHosts, "Invalid Host", http, none, false);
        testSection(invalidPorts, "Invalid Port", url, none, false);
        testSection(invalidPaths, "Invalid Path", url, none, false);
        testSection(invalidQuerys, "Invalid Query", url, none, false);
    }

    public void testIsValid(String url, String type, String value, boolean expected) {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        boolean actual = urlVal.isValid(url);
        String message = url;

        if (actual != expected) {
            if (type != "") {
                message = String.format("%s with %s of '%s'", url, type, value);
            }
            System.out.println("\tFAILED: ");
            System.out.println(String.format("\t\tExpected %s to be %s, instead got %s.", message, expected, actual));
        }
        else {
            System.out.println("\t.");
        }
    }

    public void testAnyOtherUnitTest() {}

    public void testSection(String[] values, String type, String preText, String postText, boolean expected) {
        String url;

        System.out.println(String.format("Testing %s's...", type));
        for (int i = 0; i < values.length; i++) {
            testIsValid(preText + values[i] + postText, type, values[i], expected);
        }
        System.out.println(String.format("Done testing %s's.\n", type));
    }

    public void printHeader(String type) {
        System.out.println(String.format("\n******* Testing %s *******\n", type));
    }

    public static void main(String[] argv) {
        UrlValidatorTest fct = new UrlValidatorTest("url test");
        fct.testManualTest();
        fct.testYourFirstPartition();
        fct.testYourSecondPartition();
        fct.testAnyOtherUnitTest();
    }

    // https://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
    String[] invalidSchemes = {
            "://",
            "$",
            "http:/",
            "123"
    };
    String[] validSchemes = {
            "",
            "aaa://",
            "http://",
            "z39.50s://",
            "file:///"
    };

    String[] invalidHosts = {
            "0.0.0",
            "0.0.0.256",
            "@#$%",
            "-1.0.0.0",
            "test.invalid",
            ""
    };
    String[] validHosts = {
            "www.google.com",
            "test.ac",
            "test.zw",
            "0.0.0.0",
            "255.255.255.255"
    };

    // 0 - 65535 valid
    String[] invalidPorts = {
            "-1",
            ":65536",
            ":a",
            "123"
    };
    String[] validPorts = {
            ":0",
            ":80",
            ":65535",
            ""
    };

    String[] invalidPaths = {
            "/../",
            "///",
            "abc",
            "123"
    };
    String[] validPaths = {
            "/test/test2/",
            "/$123",
            "/",
            "#anchor"
    };

    String[] invalidQuerys = {};
    String[] validQuerys = {
            "",
            "?test",
            "?test=1&test2=other"
    };
}