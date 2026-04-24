# Using the terminal

These steps are for **Apple computers** using **macOS** only. If you are not sure what that means, read [Apple computers (read this if any of this is new)](index.md#apple-computers-read-this-if-any-of-this-is-new) first.

**Goal:** open an app called **Terminal** and run three small commands—**where am I**, **what’s here**, **go to a folder**. That is all this page asks.

Read [The command line](command_line.md) if the idea of typing to the computer is new.

---

## Open Terminal

**Terminal** is an app that comes with macOS. To open it (or any app), use the built-in search called **Spotlight**:

See: [Open apps with search (Spotlight) on a Mac](open_apps_with_spotlight_mac.md).

Once Terminal is open, continue below.

---

## Try these three commands

You only need three words for now:

| Command | Plain meaning |
|--------|----------------|
| `pwd` | Where am I right now? (shows the folder path) |
| `ls` | What is in this folder? |
| `cd` | Go into a folder (example below) |

Type `pwd`, press **Enter**, and read the path. That is your **home** folder (your main user area).

Type `ls`, press **Enter**, and you will see names like **Desktop** and **Documents**—the same folders you might see in the **Finder** (Apple’s file browser), shown as text.

To visit your Desktop, type `cd Desktop`, press **Enter**, then type `ls` again to see what is on the Desktop. To step back to your home folder, type `cd ..` and press **Enter**.

That is the whole tour. You do not need anything else on your first day.

---

## If something looks odd

Wrong folder after `cd`? Type `cd` alone and press **Enter**—that usually takes you home. A command will not stop? Press **Control + C**. Most problems are a typo in the folder name; run `ls` to see exact names.

---

## Paste and safety

You can **paste** with **Command + V** (the **Command** key is labeled **⌘** and sits next to the space bar on Apple keyboards). Before you paste a line from the internet, read it and only use sources you trust. If the computer asks for your **password**, stop unless you know why that step is safe. For the big picture on typing to the computer, read [The command line](command_line.md); for paths that contain spaces, read [spaces in file names and the command line](filename_spaces_command_line.md).

---

**Check your understanding:** You are in Terminal and you want to see a list of files in the folder you are in right now. Which single command do you type?
