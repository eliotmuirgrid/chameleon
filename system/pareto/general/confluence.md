# Confluence (Atlassian wiki)

**Summary:** **Confluence** is Atlassian’s **team wiki** in the **browser**. Teams use it for **documentation**, **meeting notes**, and **linked** pages inside **one** product. Like other **closed** setups, it tends to be **easy** at first and **harder** to **export**, **restructure**, or **pipe** to **outside** tools (including **AI**) as **plain text**. For that pattern, see [Open systems vs closed systems](open/versus/close.md) and [Wix vs plain files](wix.md).

---

## What Confluence is

- **Vendor:** Atlassian (same company as **Jira**, **Bitbucket**, etc.).  
- **What you do:** Create **spaces** and **pages** in a **web** UI; **link** pages; **permissions** for teams.  
- **Where it runs:** **On Atlassian’s** infrastructure (cloud) or **self-hosted** in some setups—either way, the **experience** is **their** product, **not** “a folder of files on your disk” by default.

For how **Bitbucket** (Git hosting) relates to **Git** itself—same vendor family, different product—see [GitHub, Bitbucket, and Git](../../computer/git/github_bitbucket_and_git.md).

---

## Why it shares issues with other closed tools (e.g. Wix)

The **product** is different from a site builder, but the **shape** is similar to what [Wix vs plain files](wix.md) and [Markdown](markdown.md) describe:

| Topic | What tends to happen |
|------|------------------------|
| **Start** | **Fast** to make pages and **invite** people. |
| **Format** | Content lives **inside** Confluence’s **model**, not as **simple** `.md` or `.txt` you can **open anywhere**. |
| **Long run** | **Hard** to treat the whole body of work as **portable plain text**; **open** stacks ([Markdown](markdown.md) + [source control](source/control.md), often [Git](../../computer/git/git.md)) usually **age** better for **reuse** and **diffs**. |
| **AI** | Assistants work best on **text you control** in **files**. Pulling **clean** text **out** of a wiki is often **slower** and **more brittle** than editing Markdown **directly**. |
| **Structure** | **Moving** or **renaming** many linked pages can be **manual** and **tedious**—because the **tree** is **owned** by the **app**, not by **files you reorder** in a folder. |

Same **closed** pattern in another category: [Wix vs plain files](wix.md). Open stack: [Open systems vs closed systems](open/versus/close.md), [Markdown](markdown.md), [source control](source/control.md), [Git](../../computer/git/git.md), and [GitHub, Bitbucket, and Git](../../computer/git/github_bitbucket_and_git.md) for Atlassian-adjacent hosting context.

**How we used Confluence for an earlier concepts site**—and the **ideas** behind that site regardless of tool—is **not** covered here; see [How this all started](../../beginning.md).
