/**
 * @brief Macro for iterating over a range with a step size, starting from a and ending at b-1.
 *
 * @param i The loop variable.
 * @param a The starting value.
 * @param b The ending value (exclusive).
 */
#define FORLT(i, a, b) for (i = a; i < b; ++i)

 /**
  * @brief Macro for iterating over a range with a step size, starting from a and ending at b.
  *
  * @param i The loop variable.
  * @param a The starting value.
  * @param b The ending value (inclusive).
  */
#define FOREQ(i, a, b) for (i = a; i <= b; ++i)

  /**
   * @brief Macro for iterating over a range with a step size, starting from a and ending at b-1, with a specified step size.
   *
   * @param i The loop variable.
   * @param a The starting value.
   * @param b The ending value (exclusive).
   * @param s The step size.
   */
#define FORLTSTEP(i, a, b, s) for (i = a; i < b; i += s)

   /**
    * @brief Macro for iterating over a range with a step size, starting from a and ending at b, with a specified step size.
    *
    * @param i The loop variable.
    * @param a The starting value.
    * @param b The ending value (inclusive).
    * @param s The step size.
    */
#define FOREQSTEP(i, a, b, s) for (i = a; i <= b; i += s)

    /**
     * @brief Macro for error checking. If the condition x is equal to fail, it prints an error message with the file name and line number, and terminates the program.
     *
     * @param x The condition to check.
     * @param fail The value that x should be equal to in order to trigger the error.
     * @param message The error message to display.
     */
#define NASSERT(x, fail, message) if (x==fail) { printf("%s:%d error: %s\n", __FILE__, __LINE__, message); __builtin_trap(); }
#define ASSERT(x, pass, message) if (x!=pass) { printf("%s:%d error: %s\n", __FILE__, __LINE__, message); __builtin_trap(); }