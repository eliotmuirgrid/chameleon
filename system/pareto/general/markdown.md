# Markdown (plain English)

**Markdown** is writing with **simple typing rules** on top of **plain text**. You use a few marks for headings (`#`), bold (`**like this**`), and lists (`-`). Files usually end in **`.md`**. Any computer can open them. Apps can **show them pretty** (that is called **rendering**) or you can read the raw text as-is.

It is a **general-purpose** tool for text: **one** small set of rules covers **many** jobs—notes, school papers, project docs, books, checklists, meeting logs, web drafts, and more. You are not meant to buy a **different file format** for each kind of writing. The same idea is spelled out for physical tools in [general-purpose tools](general_purpose.md): a **few** flexible tools often beat a **drawer** of one-off gadgets.

---

## Why Word and PDF are a bad long-term bet

Word (`.docx`) and PDF **look** normal because almost everyone can open them. But the file is **not** just words. It is a **thick package** of layout, fonts, and hidden junk. That makes them a **weak place to store knowledge** if you care about the next ten or twenty years.

- **Keeping history** — **Terrible** for things that must last (**medical records**, court notes, lab work). You often get a **frozen picture** or a messy file—not a clean story of **what changed** over time.  
- **Tracking changes** — Hard to see **who changed what** in a simple way. Plain text makes that **much easier**.  
- **AI and other tools** — Harder to **read and use** than straight text. Tools work best when **the words in the file are the whole story**.  
- **Mess building up** — Every “fix” to layout adds **noise**. The file **drifts**. The meaning gets **harder to find**.

For serious work, Word and PDF are a **worse base** than plain text formats like Markdown.

---

## HTML should be legacy too (for how we write and store work)

**HTML** is what web pages are built from, but it is **more complicated than it needs to be** for **everyday writing**. Tags, nesting rules, and browser quirks pile on **noise** when you could be thinking about your ideas.

Writing **software that renders HTML “the way browsers do”**—and stays **compatible** with the real, messy web—is **extraordinarily hard**. The engines behind major browsers are **massive**. Building something like **Chromium** (the open-source core that **Chrome** is built from) from source can take **hours** even on a **powerful** computer. That is one sign of how **heavy** full HTML compatibility really is.

**Markdown is still a better place to live** for drafts and archives. When you need a web page, tools can **turn Markdown into HTML** at the end. You get the **simple file** while the web still gets HTML **when it must**.

---

## Why Markdown is a better default

- **Plain text** — What you save **is** what you see. **Less clutter** inside the file.  
- **History** — Pairs well with [source control](source_control.md) (here, [Git](../../computer/git/git.md)): you can **follow changes** over time.  
- **Search, scripts, AI** — Easy to **find text** and **hand it to a program** without extra steps.  
- **General-purpose by design** — You learn **one habit** (headings, lists, emphasis) and reuse it everywhere. That is **less to remember** than learning separate tools or export paths for each project. Same spirit as keeping a **chef’s knife** instead of ten single-job slicers—see [general-purpose tools](general_purpose.md). The **big picture** for plain files vs locked platforms is [Open systems vs closed systems](open_versus_closed.md). [Source control](source_control.md) is the idea; [Git](../../computer/git/git.md) tracks changes in practice.

---

## Quick definitions

| Word | Simple meaning |
|------|----------------|
| **Plain text** | Letters and symbols you can open in **any** text editor. No secret box inside the file. |
| **Render** | Show the file with **nice** headings and bold instead of raw `#` and `**` marks. |
