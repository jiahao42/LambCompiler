//LambLexer
//by James 2017/04/06

#ifndef LAMBLEXER_TEST_H_
#define LAMBLEXER_TEST_H_

#ifdef TEST_ON

/*
 * Simple Test Framework
 */
#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        if (!equality) {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
        }\
    } while(0)

#else
#define EXPECT_EQ_BASE(equality, expect, actual, format) do{} while(0)
#endif /* end of TEST_ON */
	
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength + 1) == 0, expect, actual, "%s")
#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")
#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")

void test_lexer();


#endif /* end of LAMBLEXER_TEST_H_ */