# Assignment-2-Code

In qudratic_probing.h, I created a new function to get the probe count by using the logic in FindPos() and counting the number of probes by counting the intial probe and every time there was a collision.

In linear_probing.h,  I created a FindPos function similar to the FindPos function used in the qudratic_probing.h file. The only diffrence is that that function moves to the next slot sequentially each time instead of moving in a wudratic sequence. I also created a function to get the probe count by using the logic in FindPos()

In double_probing.h, FindPos() was also similar to the FindPos() in the qudratic_probing.h file. The offset was calculated using the hash function described in the textbook. I also created a function to get the probe count by using the logic in FindPos().

I made sure to match my outputs to the expected outputs. (aside from the collisions)