/* The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles, Kliplab
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */
#ifndef KLIP_FRAMEWORK_FSM_H
#define KLIP_FRAMEWORK_FSM_H


/** Finite State Machine
*/
class Fsm
{
public:

    typedef void (Fsm::*FsmCallback)(void);

    Fsm();

    /** Initialize the finite state machine
     *
     * Use this functions when you are outside this fsm
     *
     * @param state         New state
     * @param call          State function
     * @param first         State initialization function
     */
    void init(int state, FsmCallback call, FsmCallback init);

    /** Run the finite state machine
     */
    void update();

    /** Is the current state egual to a specific state ?
     *
     * @param state         State to test
     * @return True if we are in the state, else false
     */
    bool isInState(int state);


    /** Is the current state initialized ?
     *
     * @return True if the current state is initialized, else false
     */
    bool isStateInitialized(void);

protected:
    /** Set the FSM to a new state
     *
     * Use this function when you are inside a state of THIS fsm
     *
     * @param newstate      New state
     * @param call          State function
     * @param first         State initialization function
     */
    void set(int newstate, FsmCallback call, FsmCallback init);


    int mCurrent;           /**< Current state of the automate */
    int mOld;               /**< Previous state */
    bool mInit;             /**< Init the state */
    FsmCallback mInitCall;  /**< Initializer's code */
    FsmCallback mCall;      /**< Updater's code */
};


#endif
