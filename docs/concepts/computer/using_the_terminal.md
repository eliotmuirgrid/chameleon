# Using the terminal (macOS)

This guide is **only for macOS**. It walks you through real steps in the **Terminal** app: see where you are, list a folder, and move to another folder. Read [The command line](command_line.md) first if you want the idea in plain terms.

---

## 1. Open Terminal

1. Press **Command + Space** to open Spotlight.
2. Type **Terminal** and press **Enter**.

(Alternatively: open **Finder** → **Applications** → **Utilities** → double-click **Terminal**.)

A window opens with a line ending in a **prompt** (often a `%` if your Mac uses **zsh**, which is the default on recent macOS). The cursor sits after the prompt, waiting for you to type.

---

## 2. See which folder you are in (`pwd`)

**`pwd`** means “print working directory.” It shows the full path of the folder Terminal is using right now.

1. Type exactly: `pwd`
2. Press **Enter**.

You should see something like `/Users/yourname`—that is your **home** folder. Every command runs **in** this folder unless you change it.

---

## 3. List what is in that folder (`ls`)

**`ls`** lists files and folders in the current directory.

1. Type: `ls`
2. Press **Enter**.

You will see names listed in columns, for example **Desktop**, **Documents**, **Downloads**—those are folders inside your home folder. This is the same material you would see in a Finder window, but as text.

To see more detail (sizes, dates, hidden files that start with `.`), you can run:

```text
ls -la
```

The `-la` part is optional: **`-l`** means long listing, **`-a`** means include hidden items.

---

## 4. Change to another folder (`cd`)

**`cd`** means “change directory.” After you run it, the **working directory** changes, so the next `ls` or `pwd` applies to the new place.

Example: go to your Desktop.

1. Type: `cd Desktop`
2. Press **Enter**.

If the name has a space, either put it in quotes (`cd "My Folder"`) or escape the space—quotes are easier.

3. Confirm where you are: type `pwd` and press **Enter**.  
   You should see a path that ends with **Desktop**, for example `/Users/yourname/Desktop`.

4. List what is on the Desktop: type `ls` and press **Enter**.

You have now **listed** one directory (home), **changed** to another (Desktop), and **listed** again in the new place.

---

## 5. Go back up one level (`cd ..`)

**`..`** is a special name meaning “the folder above this one.”

1. Type: `cd ..`
2. Press **Enter**.
3. Type `pwd` — you should be back in your home folder (path no longer ends in `Desktop`).

---

## 6. Go straight to your home folder (`cd` or `cd ~`)

Any time you want to reset to your home directory:

- Type `cd` with nothing after it and press **Enter**, or  
- Type `cd ~` and press **Enter** (`~` is shorthand for your home folder).

---

## 7. If something goes wrong

- **“No such file or directory”** after `cd` — the folder name does not exist in the current location, or you mistyped it. Run `ls` to see valid names, or check spelling and spaces.
- **Nothing seems to happen** — some commands print nothing on success; use `pwd` or `ls` to check.
- **A command runs forever** — press **Control + C** to stop it.

---

## 8. Copy, paste, and history (in Terminal on a Mac)

- **Paste** a command: **Command + V** (or Edit → Paste).
- **Copy** text from the window: select with the mouse, then **Command + C**.
- **Previous command**: press the **Up arrow** to bring back the last line you ran; edit it if needed and press **Enter** again.

---

## 9. Before you paste a command from the web

Read the whole line. Only run commands from sources you trust. If macOS asks for your **password**, it is because the command needs elevated permission—say no unless you understand why.

---

## See also

- [The command line](command_line.md) — what this window is for, in general terms.
