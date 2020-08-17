# SparkFun_Pro_Micro_Qwiic_Mux_SX1509_Multi_Joystick
Joystick project using MatthewH's Joystick library and SparkFun's SX1509 libary that allows for high inputs using I2C expanders across a MUX, thereby allowing high input counts across a single Arduino connected via USB

Project Background:

This project is intended to be used with the flight simulator DCS World.  This project was started after the existing solutions I saw were inefficient from a cost and resource standpoint.  Existing high I/O solutions used in cockpit simulators use multiple expensive Arduino Mega's in a modular Master/Slave configuration or simply rely on each Arduino Mega to have its own USB port.  I want a solution that was more cost efficient per pin, while only occupying 1 USB slot.

A)  I'm only using it exclusively in VR for a mixed reality cockpit.  I have no need to drive outputs for displays, LED's, servos, etc.  Nor do I value driving magnetic switches.

B). I'm going for a joystick device rather than DCS bios because dcs bios locks your setup to one plane (unless you re flash your Arduino every time you hop in something else)
Since I'm using a joystick device I can use the pit features for other planes should I choose to even though my cockpit is all positioned for an F/A 18c hornet and I'll only ever be in VR.  (I've already gotten used to my jacked up location for gear and hook that I threw together as a proof of concept but have flown like that for over a year on the basic layout of an A-10)

C) When designing the electronics layout, having an Arduino board for every module like others have done makes no sense to me.  It wastes USB ports and is expensive per I/O pin.  It is however modular which is attractive for those who want to slowly add to their pit a little at a time or only add the modules they actually want physical representations of.  It also means having no method of I/O expansion which I suppose is attractive for ease of understanding the system. (though my retort is having to set up a master/slave system...)

D) if you are going with a port expander and/or master slave method, you can basically choose between SPI and I2C, shifting bits or routing addresses respectively.  It seems lots of people using SPI with master/slave Arduinos spread around their pit in modules.  Maybe that design is why most seem to choose SPI?  I2C seem superior to me though.

E) Disbursing any sort of pcb board physically around the pit makes no sense to me.  Perhaps if you have a giant pit that you break down and reassemble regularly?  What I've chosen to do is centralized the I/O receptacle pins (they all fit basically in the palm of your hand); if I need to put a break in long run wires at strategic points for physical module break down reasons I can.  This also means that every line going into the board is just carrying and On/Off signal (maybe a resistance value if I'm forced to use pots over encoders)  I don't need to worry about wires acting like antennas messing up clock or data lines.

F) About encoders as axis controls.  DCS is the bottle neck because they don't allow encoders as CW/CCW controls yet.  You have to fake it or use software (which I'm thinking might add some unnecessary lag) to change how far each click on the encoder moves your dial, or deal with twisting an encoder a lot just for a little movement in game.  The good thing about encoders is you don't have to physically match the position of your dials to what's in game; they natively always "match".  If you're using pots and start your flight with mismatched positions, you're going to discover that the first manipulation you do on your pit will snap the all the switches and dials on the plane to whatever your physical pit is.  That might be really bad or mildly annoying.

G) The Windows limit for 1 Joystick device is 128 buttons, before you need to create a second virtual device.  MatthewH's library allows for this.  Similarly the axis limitation is 8.  Given my reasoning in section F, using axis controls (potentiometers) to match where the real cockpit would use them is not necessary.  No incremental knob or dial is critical to me in the sense that its position and effect needs to be determined purely from tactile sensation without glancing at the knob or dial or observing the effect.

Electronics Architecture:

The entire architecture is based around SparkFun's QWIIC system.  This system is a modular I2C system comprised of many sensors and break out boards for a variety of projects.  The base Arduino I've chosen is their Pro Micro (QWIIC version).  This allows a simple hook up to their line of I2C devices.  The next most notable component is the use if the SparkFun SX1509 16 pin I/O expander.  This device can be assigned with 4 unique addresses thereby allowing up to 64 pins when chained together on the same I2C bus.  The key to breaking that 64 pin limit lies in the next device: the 8 channel MUX.  This allows you to use multiple devices with the same I2C address by allowing the MUX to act as a funnel for your pin scans.  By duplicating the same 4 SX1509 set behind 4 channels of the 8 available channels, you get up to 256 buttons.

The intent is to not require the use of a button matrix as I value simplicity and button reliability.  I don't value having to create a button matrix which requires more complex routing of wires between various locations on the cockpit and may induce bounce/noise issues over having a super high I/O count for little pin useage.  I value ease of assembly and a wiring concept that is easily understood by others assemblying cockpits based on this project.  However, I recognize that some common cockpit items like multiple DDI's/MFD's which contatin 20 buttons each, would easily fit on a single 16 pin I/O expander.  The Hornet has 3 such devices and could fit all 60 buttons on a single 16 pin I/O expander using 8x8 pins with an extra 4 pins (8*8=64)

Software:

The software is relatively straight forward when everything is configured to act as a push button or switch.  You use the MUX to channel your commands to set all the pin modes for the I/O expanders and then change to the next MUX channel and repeat for the next set.  A matrix of button states is created for each virtual joystick and then each pin is checked in a similar scan as it updates the state for anything that has changed.  The entire system gets rescanned over and over and updates the joystick buttons states accordingly.

The default SparkFun SX1509 libary was found to be relatively slow and inefficient.  And entire scan of 256 buttons across two joysticks took approximately 260 ms or about 1 ms per button.  The default library called for an I2C speed of 100 khz and that was updated to the maximum supported speed for the components; 400 khz.  This dropped the scan time to about 100 ms per 256 buttons.  The default SparkFun SX1509 library contains functions unrelated to our use and was stripped out by Brian Charles.  It had the biggest impact and dropped the scan time to 5ms per 256 buttons.

The default behavior with MatthewH's joystick library updates the HID state via USB upon detection of a change.  With Brian Charles suggestion, the default behavior was changed to store these state change detections and update the entire USB HID state once per scan.  In theory, this should have saved time as well.  Oddly though, this resulted in and extremely laggy performance of multiple seconds for state changes to be detected or even reconnized as momentary buttons needed to be held for a few seconds before they were detected.  

About Encoders:

The problem with encoders behind I/O expanders and a MUX is that all the existing Arduino libraries aren't written with these in mind.  From a hardware standpoint, encoders generally require the need to quickly detect changes in their state.  Encoders have 3 pins, 1 for a common ground, 1 for "clockwise" and one for "counterclockwise".  It's not appropriate to think of these as momentary rotational switches.  What its doing is 2 bit quadrature code across these 2 pins.  Since each pin can only be 0 or 1, based of tiny changes in the contacts underneath those pins as you rotate it, you can have 1 of 4 possible states:  11, 01, 00, or 10 before returning to 11.  Most encoders (with or without detents) are of type x4, meaning that for every detent the encoder will sweep through those for states before returning to the same quatrature state.  This sweep through 4 states is commonly and confusingly called a single "pulse" where there is technically 4 state changes per pulse.  It's in this sweep that direction is determined because by comparing each state to the previous as it moves mechanically through those contacts underneath the pin.  This tends to happen very fast in most encoder applications, but mosts systems reading them put them on an interrupt, where if a state changes, everything else stops until it deals with that computationally.  Interestingly x1 encoders that do one state change per detend would work perfectly, but those are seen as antiquated for older applications where the processor couldn't keep up.

The most popular encoder library comes from PaulStoffregen.  His library allows the use of interrups on both pins, 1 pin, or no pins, each with degrading performance as you go towards no interrupts.  This is important with motors or basically anything other than a hand controlled dial.  The problem is that no library, including his, works with pins behind I2C I/O expanders; it just wasn't archictecture that was expected when it was made.  Most encoder handeling all but requires it to be on an interrupt pin, which is generally a hard limit based on the chosen Arduino.  Thats makes high encoder counts constrained to the chosen board.

Since we're limited to at least 5ms per scan cycle, that means I can miss encoder state changes if it changes quadrature faster than a scan cycle could detect.  Given that the use case for the encoder is to effectively act as a button for CW or CCW usage and is not meant to detect speed of rotation or position, I made it error tolerant.  First, most encoders have 24 pulses per revolution.  Since we know that each pulse covers 4 state changes, we get 96 state changes per revolution.  Since we cannot change state faster than 5ms, we're left with a theoritical speed of about 2 RPS.  (96 x 5 ms = 480ms.  480 ms / 1 rev = 2.083 rev / second)  Spinning somethign that fast for our appliction doesn't seem necessary as no cockpit dial needs to be spund that fast or is expected to be spun that fast.

The error tolerant method looks and the current quadrature state as well as the previous three states and makes assumptions about the most likely direction of travel.  It naturally will detect a perfect quadrature histroy and return the appropriate CW/CCW direction.  (4 possible CCW and 4 possible CCW to an from any of the 4 possible states) The error tolerance comes in by assuming it a scan completely skipped one of the three previous states.   This expands the solution by another 12 possible CW and 12 CCW assumptive historys.  ( a total of 32)  If we only concern our selves with the previous two states, again accounting for perfect and state skips at either previous state, we add another 24 assumptive directions.  If we only keep track of the previous state, again accounting for error, we add another 8 assumptive directions.  This is all summarized in the included Encoder Logic Error Handling.xlsx file.  Since this is reduced to 8 bit binary there are a maximum of 256 combinations.  A total of 64 perfect and assumtive states exist which can only occur 1/4th of the time.  (24 of the 64 are perfect state changes)  Once a state change of perfect or assumtive direction is detected, the appropriate button is pressed and held until the encoder has remainded still for the current and previous three state scans.

With 9 encoders as part of the 256 buttons, the complete scan time went up from 5ms to 20ms.  Disproprotionate, but as each encoder taps into a function to handle this, its expected.  In theory this makes the max scan time about 1/2 rev per second.  Interestingly, this is about right for DCS as pressing the appropriate CW/CCW button doesn't spin the encoder on screen all that fast.  If you try to approximate it visually, you'll be fine.  If you zing it like a top or try to crawl slower, it won't work.
