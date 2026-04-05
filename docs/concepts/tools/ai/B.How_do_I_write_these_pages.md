# How I write these pages

I use a small set of steps over and over. It is a **pipeline**: rough input, then assembly-line refinements, until the communication is **clear enough to share**. Nothing here is magic—it is **iteration**. The **precise tools** matter **less** than the **thought process** (seed → distill → constrain → shape → share → revise). What follows names **ChatGPT** and **Cursor** because that is what I use; you could swap in other assistants or editors and keep the same rhythm.

---

## Step 1 — Seed a rough message in ChatGPT

I start in ChatGPT with something informal—often dictated or typed quickly—labeled so I remember what it is for. Example **seed** (“Flow”):

> Could I help you learn to use ChatGPT in our communication via text to communicate better? While I love the sound of your voice. I can process text faster and ChatGPT will help you focus your thoughts and communicate faster—this is part of the process. I can help you get a paid version of ChatGPT as an app on your phone—the one which accepts dictation—that makes it very fast to give it a few points, have it format the message, you can read and see if it works.

---

## Step 2 — Let the model expand and clean it

ChatGPT turns the seed into a fuller, smoother message (same intent, better shape). I treat that as the first **organized** version of the idea—not the final page, but a draft I can steer.

**What came back** from the Step 1 prompt:

> Could I help you use ChatGPT as part of how we communicate? I genuinely enjoy hearing your voice, but I find I can process text much faster—and with ChatGPT, it becomes easier to organize thoughts and express them clearly without losing meaning.
>
> It could be a really useful part of how we connect. You could speak your ideas using dictation, give it a few rough points, and let it shape them into something structured. Then you can quickly review it, adjust anything that doesn’t feel quite right, and send it. It keeps things natural, but adds clarity and speed.
>
> If it helps, I’m happy to set you up with the paid version on your phone—the one that supports dictation smoothly. It makes the whole process feel effortless, like thinking out loud but communicating with precision.

---

## Step 3 — Distill keywords

The keywords are **distilled from the Step 2 draft**, not from the rough seed in Step 1. Concretely: they summarize the **three paragraphs** in the **What came back** blockquote in Step 2 (voice vs text, dictation workflow, offer to help with the app). I either keep that reply in the same ChatGPT thread so “this” still refers to it, or **paste those paragraphs in** so the model is looking at the same text.

Example prompt:

> Distill this into a set of keywords—I often use you for this exact purpose.

A typical **response** (labels for *that* expanded message) looks like this:

- Clarity  
- Speed  
- Structure  
- Focus  
- Compression  
- Expression  
- Iteration  
- Refinement  
- Signal-over-noise  
- Asynchronous thinking  
- Dictation → organization  
- Thought → text → improvement  

In other words, this list **compresses the Step 2 message** into labels. Those words are **anchors** for Step 4. Some of them will sound unfamiliar to many readers if you leave them bare on the page—but that is fine here. The list is not the final voice; it is a **map** of what matters.

---

## Step 4 — Turn the keywords into plain-English prose

Next I feed the same keywords back in with a stricter constraint: a few paragraphs of **plain English**—clear enough for someone with a **high-school-level** reading level—while still using the list to **seed** the ideas (not to sound like jargon).

I would ask for that **even if** the audience were the strongest PhDs in the room. **Simpler is almost always clearer**, and it matches an **80/20** instinct for communication: a little extra care up front reaches far more people, with less noise.

Example prompt shape:

> Explain in a few paragraphs how using a tool like ChatGPT to communicate over text results in faster communication and a better thought process. Use these words to seed your points but express the ideas in plain English someone with a high school education could understand:  
> Clarity, Speed, Structure, Focus, Compression, Expression, Iteration, Refinement, Signal-over-noise, Asynchronous thinking, Dictation → organization, Thought → text → improvement.

That pass produced the **long draft** that became the core of [A. Communicate better and faster with AI](A.Communicate_better_faster_with_AI.md) (sketch analogy, speed/structure, step-by-step refinement, your own pace—before I edited layout and headings).

---

## Step 5 — Move to Cursor and a Markdown file

I open **Cursor** (an AI-assisted editor), create a new file such as `A.Communicate_better_faster_with_AI.md`, and paste the draft.

**Markdown** is a simple way to add structure in **plain text**: light conventions (`#` for headings, `**bold**` for emphasis, `-` for lists) instead of a heavy word processor. Files usually end in `.md`; the source stays readable as-is, and tools like GitHub or many editors can **render** it into clean, scannable pages. **These pages are written in Markdown.**

That choice matters here: you can open and edit the file with nothing more than a text editor—no special vendor lock-in—and the same bytes are easy for **both people and AI** to read, quote, and reshape. Binary or heavily wrapped formats (typical **Word** or **PDF** workflows) usually need extra software or conversion before you can treat the text as plain, processable language. For drafting, revising, and getting help from an assistant, Markdown tends to be the smoother path end to end.

---

## Step 6 — Format and tighten in the editor

I select the text, open chat **in** the editor, and ask for something like:

> Format this more clearly for clarity.

That pass adds **headings**, **sections**, **emphasis**, and anything else needed so the page is easy to scan.

---

## Step 7 — Real feedback, then one more pass

I share the page with someone I care about. A real **objection** showed up:

> It feels like I'm cheating by using a different format to communicate; in other words, it doesn't feel like it's coming from me.

Then I prompted Cursor along these lines:

> Add a paragraph/heading to counter this objection **that** many people have. The reality is that using AI in this way actually modifies how you think and trains your mind. It **changes** you and grows your ability to think. This is a major tool I have used to improve my own consciousness.

That became the section **“Doesn’t this weaken your thinking?”** on the A page.

---

## What to take away

The steps, in order: start **rough** → get a **fuller** version → pull out **keywords** → write a **plain draft** that follows clear rules → move it into a **Markdown file** → **tidy** the layout → let a **real person** read it → **fix** what still feels off.

The software is not doing your thinking for you. It helps you **tighten** and **organize** what you already meant to say. Each time you run through the steps, you usually get a little **sharper** the next time.
