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

    public UrlValidatorTest(String testName) {
        printHeader("isValid");
    }

    /**
     * Tests various specific cases manually
     */
    public void testManualTest() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        printHeader("isValid manually");

        System.out.println(String.format("Testing valid urls..."));
        testIsValid("http://foo.com", "", "", true);
        testIsValid("http://foo.com/", "", "", true);
        testIsValid("http://foo.com/bar", "", "", true);
        testIsValid("https://foo.com/bar", "", "", true);
        testIsValid("http://foo.jp/bar", "", "", true);
        testIsValid("http://foo.ru/bar", "", "", true);
        testIsValid("http://foo.com?q=bar", "", "", true);
        testIsValid("http://foo.com?q=bar&z=baz", "", "", true);
        testIsValid("file:///foo", "", "", true);
        testIsValid("http://foo.com:80", "", "", true);
        testIsValid("http://foo.com:8080", "", "", true);
        testIsValid("http://123.221.132.231", "", "", true);
        testIsValid("http://123.221.132.231:80", "", "", true);
        System.out.println(String.format("Done testing valid urls.\n"));

        System.out.println(String.format("Testing invalid urls..."));
        testIsValid("http:///foo", "", "", false);
        testIsValid("http://foo.com?q=", "", "", false);
        testIsValid("http://foo.com:808080", "", "", false);
        testIsValid("http://123.456.789.000", "", "", false);
        testIsValid("http://111.111.111", "", "", false);
        testIsValid("http://111.111.111.111.111", "", "", false);
        testIsValid("http://foo.falsedomainname", "", "", false);
        testIsValid("77012://foo.com", "", "", false);
        System.out.println(String.format("Done testing invalid urls.\n"));
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

    public void testAnyOtherUnitTest() {
        printHeader("isValid with specific edge cases");

        // https://en.wikipedia.org/wiki/Domain_Name_System#Domain_name_syntax
        int maxLabel = 64;
        int maxHost = 253;
        String maxLengthLabel = new String(new char[maxLabel - 1]).replace("\0", "a");
        String maxLengthHost = "";
        for (int i = 1; i <= maxHost; i++) {// 253 - 4 for .com => 249
            if (i % maxLabel == 0) { // 0-63 chars max per label
                maxLengthHost += '.';
            }
            else {
                maxLengthHost += 'o';
            }
        }

        System.out.println(String.format("Testing max domain length of %d chars ...", maxHost));
        testIsValid("http://" + maxLengthHost + ".com", "", "", true);
        testIsValid("http://" + maxLengthHost + ".a.com", "", "", false);    // 254 chars domain (1 over)
        System.out.println(String.format("Done testing max domain length of %d chars.\n", maxHost));

        System.out.println(String.format("Testing max domain label length of %d chars ...", maxLabel));
        testIsValid("http://" + maxLengthLabel + ".com", "", "", true);
        testIsValid("http://" + maxLengthLabel + "a.com", "", "", false);    // 64 length on end label
        System.out.println(String.format("Done testing max domain label length of %d chars.\n", maxLabel));
    }

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
            "",
            "://",
            "$",
            "http:/",
            "123"
    };
    String[] validSchemes = {
            "aaa://",
            "http://",
            "z39.50s://",
            "file:///"
    };

    String[] invalidHosts = {
            "192.192.192",
            "192.192.192.256",
            "192.192.192.192.192",
            "@#$%",
            "-1.0.0.0",
            "test.invalid",
            "test.ab",
            "test.zx",
            "invalid",
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