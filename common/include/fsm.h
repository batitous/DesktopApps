// Baptiste Burles, Kliplab, 2014
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
