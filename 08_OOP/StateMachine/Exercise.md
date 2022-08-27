# State Machine Exercise

Note: Use the modifed AC class that i have given you.

## Exercise

Implement the following state machine class:

![alt](./../../media/uml2.png)

The class should implement the following state transitions:

![alt](./../../media/state_machine.png)

The method calling order is:

1. evaluation
   1. evaluate_state (calls activatze method of the ac)
   2. evaluate_transition (executes transition change)

Note: Define a appropiate enum for the states
