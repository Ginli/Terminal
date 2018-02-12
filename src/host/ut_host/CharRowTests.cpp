/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/
#include "precomp.h"
#include "WexTestClass.h"

#include "CommonState.hpp"

#include "globals.h"
#include "textBuffer.hpp"

#include "input.h"

using namespace WEX::Logging;
using namespace WEX::TestExecution;

class CharRowTests
{
    TEST_CLASS(CharRowTests);

    CHAR_ROW* pSingleByte;
    CHAR_ROW* pDoubleByte;

    short _sRowWidth = 80;

    TEST_METHOD_SETUP(MethodSetup)
    {
        pSingleByte = new CHAR_ROW(_sRowWidth);
        pSingleByte->SetWrapStatus(true);
        pSingleByte->SetDoubleBytePadded(true);

        pDoubleByte = new CHAR_ROW(_sRowWidth);
        pDoubleByte->SetWrapStatus(true);
        pDoubleByte->SetDoubleBytePadded(true);

        return true;
    }

    TEST_METHOD_CLEANUP(MethodCleanup)
    {
        delete pDoubleByte;
        delete pSingleByte;
        return true;
    }

    TEST_METHOD(TestInitialize)
    {
        // Properties needed for test
        const short sRowWidth = 44;

        // Cases to test
        CHAR_ROW* pTestItems[] { pSingleByte, pDoubleByte };

        // Loop cases
        for (UINT iIndex = 0; iIndex < ARRAYSIZE(pTestItems); iIndex++)
        {
            CHAR_ROW* pUnderTest = pTestItems[iIndex];

            pUnderTest->Reset(sRowWidth);

            VERIFY_IS_FALSE(pUnderTest->WasWrapForced());
            VERIFY_IS_FALSE(pUnderTest->WasDoubleBytePadded());

            for (UINT iStrLength = 0; iStrLength < sRowWidth; iStrLength++)
            {
                VERIFY_ARE_EQUAL(pUnderTest->GetGlyphAt(iStrLength), UNICODE_SPACE);
                VERIFY_IS_TRUE(pUnderTest->GetAttribute(iStrLength).IsSingle());
            }
        }
    }

    TEST_METHOD(TestContainsText)
    {
        // After init, should have no text
        pSingleByte->Reset(_sRowWidth);
        VERIFY_IS_FALSE(pSingleByte->ContainsText());

        // add some text
        pSingleByte->GetGlyphAt(10) = L'a';

        // should have text
        VERIFY_IS_TRUE(pSingleByte->ContainsText());
    }
};
