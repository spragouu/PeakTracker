<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://bakkesplugins.com/plugins/view/274">
    <img src="https://media.discordapp.net/attachments/720041712390635628/874468669030268928/Webp.net-resizeimage_1.png?width=683&height=683" alt="Logo" width="220" height="200">
  </a>

  <h3 align="center">PeakTracker</h3>

  <p align="center">
    An awesome BakkesMod Plugin to keep track of your Peak MMR!
  </p>
</p>

#

PeakTracker is a plugin for [Bakkesmod](https://www.bakkesmod.com/) that tracks the users peak MMR (aka. highest achieved MMR) for all ranked gamemodes in Rocket League.

## Installation
There are two routes to install plugins either though the in-game plugin manager or from the plugin website, both take only a few seconds. But the first step before anything is to first make sure you have BakkesMod installed!
 - Download and install [Bakkesmod](https://www.bakkesmod.com/). 
### Through In-Game Plugin Manager
 - While at the main menu - Press **F2** to open the BakkesMod window
 - Select the **Plugins tab**
 - Select **Plugin Manager** located at the top of the list on the left and click the **open button**.
 - In the top right in the ID textbox - enter **274** and click **Install by ID**
 - That's it the plugin is now installed! Happy Peaking!

### BakkesPlugins Website
 - Visit the [PeakTracker plugin page](https://bakkesplugins.com/plugins/view/274).
 - Click the **Install with BakkesMod** button and follow the instructions
 - That's it the plugin is now installed! Happy Peaking!

## Additional Information & Features
PeakTracker initially will set your peak to your current MMR for each gamemode (Values are pulled at the start and end of matches). As your MMR changes, your peak (highest obtained) MMR will be saved and only update once you've reached a higher MMR!

If your peak MMR is higher than your current MMR then you can manually set your peak through the in game menu!

### In-Game Menu
![In-Game Menu](https://media.discordapp.net/attachments/720041712390635628/874102199880388628/unknown.png)

To get to this menu, while in-game press **F2** to open the BakkesMod Menu. Then select the **Plugins** tab, then finally select the **PeakTracker** plugin from the list that appears on the left.

All this information is saved in various text files in the following location: 
 - **%appdata%\Roaming\bakkesmod\bakkesmod\PeakTracker**

### CSV Output

![CSV Output](https://media.discordapp.net/attachments/720041712390635628/874459489351381032/unknown.png)

All peak information will be outputted in addition to the various text files a CSV file. The CSV file will contain more detailed information about the specific peak as shown in the screenshot above.

This will allow you to track your peak MMR progression over time or display the information anyway you want through something like Excel or a custom program! Let your imagination run wild! 🤯

The CSV file is available in the following location:
 - **%appdata%\Roaming\bakkesmod\bakkesmod\PeakTracker\PeakTracker.csv**

Instead of modifying this file directly it's reccommend that you make a copy that you then modify the copy. However, if you insist on modifying the original file make sure to leave the first line unmodified and always have an empty line at the end of the file otherwise there could be errors.

### OBS Intergration

If you use OBS and would like to add your peak MMR into your overlay you can create a **Text** source and select **Read from a file** and select the text file you want to display.

All text files are located in the following location: 
 - **%appdata%\Roaming\bakkesmod\bakkesmod\PeakTracker**

![PeakTrackerFolder](https://media.discordapp.net/attachments/720041712390635628/874110592393285712/unknown.png)

## Usage and Thanks

This project is available for free under the MIT license, feel free to do whatever you want with the code except blame me if you break something! 😅

Thank you to the BakkesMod Plugin community for helping me with any questions I had and for their great tutorials that got the ball rolling for me! Also thank you to my lovely girlfriend for making the logo!

**Happy Peaking!**
