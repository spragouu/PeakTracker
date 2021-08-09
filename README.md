# PeakTracker 📈

PeakTracker is a plugin for [Bakkesmod](https://www.bakkesmod.com/) that tracks the users peak (aka. highest achieved) MMR for all ranked gamemodes in Rocket League.

## Installation
 - Download and install [Bakkesmod](https://www.bakkesmod.com/). 
 - **FINAL INSTALL DETAILS PENDING RELEASE**.

## Additional Information & Features
PeakTracker initially will set your peak to your current MMR for each gamemode (Values are pulled at the start and end of matches). As your MMR changes, your peak (highest obtained) MMR will be saved and only update once you've reached a higher MMR!

If your peak MMR is higher than your current MMR then you can manually set your peak through the in game menu!

### In-Game Menu
![In Game Menu](https://media.discordapp.net/attachments/720041712390635628/874102199880388628/unknown.png)

To get to this menu, while in-game press **F2** to open the BakkesMod Menu. Then select the **Plugins** tab, then finally select the **PeakTracker** plugin from the list that appears on the left.

All this information is saved in various text files in the following location: 
 - **%appdata%\Roaming\bakkesmod\bakkesmod\PeakTracker**

### CSV Output (Not Implemented Yet)

All peak information will be outputted in addition to the various text files a CSV file. The CSV file will contain more detailed information for the specific peak such as date achieved, associated rank (Diamond I, etc.), and more.

This will allow you to track your peak MMR progression over time or display the information anyway you want through something like Excel or a custom program! Let your imagination run wild! 🤯

The CSV file is available in the following location:
 - **%appdata%\Roaming\bakkesmod\bakkesmod\PeakTracker\PeakTracker.csv**

**This specific feature is still a work in progress and once implemented a screenshot of the additional data that's being captured will be added :)**

### OBS Intergration

If you use OBS and would like to add your peak MMR into your overlay you can create a **Text** source and select **Read from a file** and select the text file you want to display.

All text files are located in the following location: 
 - **%appdata%\Roaming\bakkesmod\bakkesmod\PeakTracker**

![PeakTrackerFolder](https://media.discordapp.net/attachments/720041712390635628/874110592393285712/unknown.png)

## Usage and Thanks

This project is available for free under the MIT license, feel free to do whatever you want with the code except blame me if you break something! 😅

I'd also like the say thanks to the BakkesMod Plugin community for helping me with any questions I had and for their great tutorials that got the ball rolling for me! 

**Happy Peaking!**