# [Symmetry](../symmetry.md) > Markdown Table Format

Always use [Markdown tables](https://www.markdownguide.org/extended-syntax/#tables) as an application of finding symmetry.

This decision is for people doing real work (like nutrition planning). A good table should be easy to scan in seconds, easy to check, and easy to discuss.

Markdown tables are easier to read on sight. People can understand the structure right away, and systems that use **artificial intelligence (AI)** can keep the meaning with less guesswork. Platforms like [GitHub, Bitbucket, and Git](../../../computer/git/github_bitbucket_and_git.md) and editors like [Cursor](../../../entity/software/cursor.md) already render Markdown tables clearly.

You can see the use of [tracking/log.md](../../../../tracking/log.md)

## Example: Markdown table

```md
| Food | Grams | Protein_g | Calories_kcal |
| --- | ---: | ---: | ---: |
| Fish, Salmon | 200 | 40 | 416 |
| Blueberries | 100 | 0.7 | 57 |
```

You can see headers, rows, and columns immediately.

## Decision

Use Markdown tables as the default format for shared data in this project.

## Older formats (for reference only)

If you run into older files, here is what they mean:

- **Comma-separated values (CSV)** means columns are split by commas.
- **Tab-separated values (TSV)** means columns are split by tab characters.

### Comma-separated values (CSV)

```text
Food,Grams,Protein_g,Calories_kcal
Fish, Salmon,200,40,416
Blueberries,100,0.7,57
```

You have to parse commas correctly, and values with commas can be confusing.

### Tab-separated values (TSV)

```text
Food	Grams	Protein_g	Calories_kcal
Fish, Salmon	200	40	416
Blueberries	100	0.7	57
```

This is cleaner than CSV for commas inside values, but tabs are still not as visually clear as a Markdown table. Visible tables support [symmetry](../symmetry.md) across related files; when machine dumps and human prose diverge, treat them as [separation of concerns](../separation_of_concerns/concept.md).

