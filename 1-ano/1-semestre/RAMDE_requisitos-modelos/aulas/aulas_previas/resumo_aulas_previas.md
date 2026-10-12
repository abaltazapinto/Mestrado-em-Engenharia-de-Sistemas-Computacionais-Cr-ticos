
## 1. Knowledge Map

Based **only on `ramde01.pdf` → `ramde05.pdf`**.

```text
Why models?
│
├─ Testing individual scenarios does not prove all behaviours
├─ Critical systems need stronger confidence / verification
└─ Abstraction reduces the problem to manageable models
        │
        ▼
Model
├─ simplified / partial representation of reality
├─ mapping feature
├─ reduction feature
└─ pragmatic feature
        │
        ▼
Model-Driven Engineering (MDE)
├─ model as central software-development artifact
├─ models as drafts
├─ models as guidelines
└─ models as programs
        │
        ├──────────────► Domain-Specific Languages (DSL)
        │
        └──────────────► Requirements Engineering
                             ├─ elicitation
                             ├─ documentation
                             ├─ validation & negotiation
                             └─ management
                                   │
                                   ▼
                             Requirement types
                             ├─ Functional
                             ├─ Quality
                             └─ Constraints
                                   │
                                   ▼
Model ↔ Metamodel
├─ model follows rules/constraints of metamodel
├─ metamodel defines modeling concepts
└─ modeling levels
        │
        ▼
Ecore / EMF
├─ Ecore used for metamodeling
└─ EMF implements EMOF concepts
        │
        ▼
RAMDE modeling approach
├─ EMF / Ecore → concepts + rules
├─ Xtext → textual DSL
└─ PlantUML → graphical projection
        │
        ▼
Light-switch demonstration
        │
        ├─ Requirements modeling
        │
        ▼
PROJECT CONCERN 1
Requirements Metamodel + DSL
├─ status
├─ priority
├─ verificationMethod
├─ risk
├─ type
├─ author
└─ Hazard → Risk → mitigated by Requirement
        │
        ▼
PROJECT CONCERN 2
Use Cases
├─ Requirement refinement: multiple references
├─ UseCase description
├─ actors in diagram
├─ optional refine-relationship display
└─ actor ↔ use-case interactions
```

### Connections between classes

**Lecture 01 → Lecture 02:** Lecture 01 motivates why abstraction/models matter in critical systems. Lecture 02 develops the concepts of model, MDE, requirements, metamodels, DSLs, EMF/Ecore and the RAMDE toolchain.

**Lecture 02 → Lecture 03:** the theory becomes the semester project. The light-switch environment becomes the demonstration that must first be replicated and then adapted/extended to the student's own domain.

**Lecture 03 → Lecture 04:** the first project concern is **Modeling Requirements**.

**Lecture 04 → Lecture 05:** requirements become inputs/references for **Use Cases**. In particular, Lecture 05 explicitly requires a `refine` relationship from use cases to requirements.

---

# 2. Coursework / Required Work Inventory

There is one major fact governing the whole UC:

> **Evaluation during the semester = individual project, 100%; no final written exam.** (`ramde01`, pp. 18–20)

It has three evaluation moments:

| Evaluation                       | Weight | Timing stated in PDF |
| -------------------------------- | -----: | -------------------- |
| M1 — ongoing project/lab work   |    40% | Weeks 3–10          |
| M2a — final practical defense   |    40% | Week 11              |
| M2b — final theoretical defense |    20% | Week 11              |

These are **course-relative weeks**, not calendar dates. The PDFs do not give calendar dates.

### A. Establish the project domain

**Task:** Select/propose the problem/domain for the individual project.

**Type:** Project / Preparation

**Source:** `ramde01`, p.18; `ramde03`, pp.2, 4–5.

**Requirements:** It should relate to critical systems. `ramde03` further requires a problem that:

- has a small number of parts;
- has at least one component whose behaviour requires state machines;
- contains a "rich" set of domain rules that can be verified/tested;
- can eventually be modeled sufficiently to generate runnable code demonstrating the majority of requirements.

**Deliverable:** Selected project topic/problem. Exact submission format is not specified.

**Deadline:** **Not covered in the provided previous-class PDFs.**

**Status:** **Unclear.**

---

### B. Maintain project work in GitHub repository

**Task:** Keep project artifacts in the student's repository.

**Type:** Project / Submission

**Source:** `ramde01`, p.18; `ramde03`, pp.2–3.

**Requirements:** All artifacts produced during the project, including documentation, must be committed to the repository.

**Deliverable:** Repository containing project artifacts.

**Status:** **Unclear.**

---

### C. Replicate each demonstrated project concern

**Task:** Replicate the teacher's demonstrations in the repository before extending them to the student's own domain.

**Type:** Lab / Code

**Source:** `ramde03`, pp.2–3.

The stated project concerns are:

`Requirements → Use Cases → Domain → State Machines → Model Constraints → Traceability → Code Generation`

Only **Requirements** and **Use Cases** have detailed implementation requirements in the PDFs currently provided.

**Status:** **Unclear.**

---

### D. Project Concern 1 — replicate Requirements example

**Task:** Replicate the **light-switch requirements modeling example**.

**Type:** Lab / Code

**Source:** `ramde02`, pp.27–33; `ramde04`, p.2.

**Requirements:** Replicate the requirements modeling example in the repository.

**Deliverable:** Replicated light-switch requirements modeling project in repository.

**Status:** **Unclear.**

---

### E. Project Concern 1 — extend Requirements Metamodel + DSL

**Task:** Extend the Requirements Metamodel and DSL.

**Type:** Code / Project

**Source:** `ramde04`, p.2.

Explicitly add support for:

- `status` — examples: Draft, Under Review, Approved, Rejected;
- `priority` — High, Medium, Low, Critical;
- `verificationMethod` — Analysis, Demonstration, Inspection, Test;
- `risk` — High, Medium, Low;
- `type` — examples include Functional, Performance, Safety;
- requirement author.

Also introduce concepts supporting:

```text
Hazard
   ↓ leads to
Risk
   ↓ mitigated by
Requirement
```

**Deliverable:** Extended Metamodel + DSL.

**Status:** **Unclear.**

---

### F. Model your project's requirements

**Task:** Use the extended DSL to model the requirements of the selected project domain.

**Type:** Modeling / Project

**Source:** `ramde04`, p.2.

**Requirements:** Use the **new extended DSL**.

**Deliverable:** Requirements model committed/pushed to repository.

**Status:** **Unclear.**

---

### G. Concern 1 technical documentation

**Task:** Document the Requirements concern.

**Type:** Report / Documentation

**Source:** `ramde03`, p.3; `ramde04`, p.2.

The generic project report requirements explicitly include:

- analysis of the problem;
- design of the solution;
- tests;
- discussion of alternatives.

Lecture 04 additionally requires technical documentation in the repository with **images illustrating the models**.

**Deliverable:** Small Markdown report + model images.

**Status:** **Unclear.**

---

### H. Project Concern 2 — replicate Use Case example

**Task:** Replicate the light-switch use-case modeling example.

**Type:** Lab / Code

**Source:** `ramde05`, p.2.

**Deliverable:** Replicated project in repository.

**Status:** **Unclear.**

---

### I. Extend Use Case Metamodel + DSL

**Task:** Extend the Use Case modeling environment.

**Type:** Code / Project

**Source:** `ramde05`, pp.2–3.

Explicit requirements:

1. Change `refine → Requirement` from **one reference to several references**.
2. Add a `description` attribute to `UseCase`.
3. Display modeled **Actors** in the generated diagram.
4. Add an optional boolean flag to `UCModel` controlling whether `refine` relationships appear in use-case diagrams.
5. Add support for modeling **interactions between actors and use cases**.

**Deliverable:** Extended Use Case Metamodel/DSL/diagram functionality capable of producing the illustrated kind of diagram.

**Status:** **Unclear.**

---

### J. Model your project's Use Cases

**Task:** Model the use cases of the selected project using the extended DSL.

**Type:** Modeling / Project

**Source:** `ramde05`, p.2.

**Deliverable:** Use-case model committed/pushed to repository.

**Status:** **Unclear.**

---

### K. Concern 2 technical documentation

**Task:** Document the Use Case work.

**Type:** Report / Documentation

**Source:** `ramde03`, p.3; `ramde05`, p.2.

**Requirements:** Technical documentation must include images illustrating **models and metamodels**. The generic project-report requirements also call for analysis, design, testing and discussion of alternatives.

**Deliverable:** Markdown technical report + images.

**Status:** **Unclear.**

---

### L. AI-use statement

`ramde01` explicitly says AI tools may support learning **with a statement about the tools used and their respective purposes**, while the student remains accountable for decisions/content.

**Type:** Documentation / Evaluation requirement

**Exact required format:** **Task identified, but requirements are incomplete in the provided PDFs.**

**Status:** **Unclear.**

---

# 3. Prioritized Coursework Backlog

I am **not interpreting Weeks 3–11 as current calendar deadlines**, because the PDFs do not map those weeks to dates.

| Priority                 | Task                                                  | Source | Prerequisite                              | Expected output                   | Deadline           | Status  |
| ------------------------ | ----------------------------------------------------- | ------ | ----------------------------------------- | --------------------------------- | ------------------ | ------- |
| **P0 — Blocking** | Select valid project domain                           | 01/03  | Understand project constraints            | Defined project topic/domain      | Not stated         | Unclear |
| **P1**             | Replicate Requirements light-switch example           | 02/04  | Model, metamodel, DSL, EMF/Xtext          | Working repository project        | Not stated         | Unclear |
| **P1**             | Extend Requirements Metamodel + DSL                   | 04     | Previous replication                      | Extended metamodel/DSL            | Not stated         | Unclear |
| **P1**             | Add Hazard → Risk → Requirement modeling            | 04     | Requirements metamodel                    | Hazard/risk support               | Not stated         | Unclear |
| **P1**             | Model own project's requirements                      | 04     | Project domain + extended DSL             | Requirements model                | Not stated         | Unclear |
| **P1**             | Document Concern 1                                    | 03/04  | Concern 1 implementation                  | Markdown + images                 | Not stated         | Unclear |
| **P1**             | Replicate Use Case example                            | 05     | Requirements work                         | Replicated use-case project       | Not stated         | Unclear |
| **P1**             | Extend Use Case Metamodel + DSL                       | 05     | Use-case replication + requirements model | Extended implementation           | Not stated         | Unclear |
| **P1**             | Model own project's use cases                         | 05     | Own requirements + extended UC DSL        | Use-case model                    | Not stated         | Unclear |
| **P1**             | Document Concern 2                                    | 03/05  | Concern 2 implementation                  | Markdown + model/metamodel images | Not stated         | Unclear |
| **P2**             | Prepare theoretical understanding for project defense | 01–05 | Concepts implemented in project           | Ability to justify decisions      | Week 11 evaluation | Unclear |
| **P2**             | Maintain AI-use statement                             | 01     | Use of AI                                 | Disclosure of tools/purposes      | Not stated         | Unclear |

For most individual implementation tasks, **priority is not explicit in the PDFs**. Their ordering above follows the dependency/order explicitly established by the project process rather than an invented deadline.

---

# 4. Must Know / Should Know / Recognition Only

## Must Know

These directly support work already assigned:

- what a **model** is;
- abstraction and purpose of models;
- MDE;
- relationship between **model and metamodel**;
- modeling levels;
- Ecore/EMF's role in metamodeling;
- DSL concept;
- Xtext's role in the RAMDE approach;
- PlantUML's graphical role;
- requirement;
- stakeholder;
- Requirements Engineering;
- functional requirements;
- quality requirements;
- constraints;
- light-switch requirements example;
- Requirements Metamodel + DSL;
- Hazard → Risk → Requirement relationship;
- Use Cases and their relationship/refinement to Requirements, as required by Lecture 05.

## Should Know

- mapping, reduction and pragmatic features of models;
- descriptive vs prescriptive purposes;
- models as drafts/guidelines/programs;
- verification/validation motivation;
- V-Model motivation;
- limitations of models/MDE;
- requirements elicitation, documentation, validation/negotiation and management;
- project evaluation rubric;
- ability to justify design options and discuss alternatives.

## Recognition Only

At the stage represented by these PDFs:

- Software Product Lines;
- variability management;
- business-centric / architecture-centric SPL;
- two-life-cycle approach;
- MDD/MDSD;
- MDA;
- MIC;
- SysML requirements modeling example;
- MBeddr;
- ATL;
- Acceleo;
- Sirius;
- MPS;
- Visual Studio Modeling SDK;
- Low-Code / No-Code discussion;
- companies/examples presented as MDE/SPL context.

The PDFs mention these, but the provided project concerns do not yet require you to implement them.

---

# 5. Dependencies: Work ↔ Knowledge

```text
Select project domain
    ↓
Project constraints from Lecture 03
    ↓
Domain must support:
parts + state-machine behaviour + rich rules + eventual code generation
```

```text
Replicate Requirements example
    ↓
Model + Metamodel
    ↓
Ecore / EMF
    ↓
DSL / Xtext
    ↓
PlantUML graphical projection
    ↓
Light-switch example
         Lecture 02
```

```text
Extend Requirements DSL
    ↓
Model/Metamodel + Requirements concepts
    ↓
Requirement types
    ↓
status / priority / verificationMethod / risk / type / author
         Lectures 02 + 04
```

```text
Hazard/Risk extension
    ↓
Extended Requirements Metamodel + DSL
    ↓
Hazard → Risk → mitigated by Requirement
         Lecture 04
```

```text
Model own requirements
    ↓
Selected project domain
    +
Extended Requirements DSL
         Lectures 03 + 04
```

```text
Model Use Cases
    ↓
Existing Requirements model
    ↓
refine → Requirement
    ↓
Use Case Metamodel + DSL
         Lectures 04 + 05
```

```text
Extend Use Cases
    ↓
Metamodel + DSL concepts
    +
Requirements references
    +
Actors / UseCases / diagrams
         Lectures 02 + 05
```

```text
Technical reports
    ↓
Completed concern
    ↓
Analysis + Design + Tests + Alternatives
    +
Images of models/metamodels
         Lectures 03–05
```

The most important dependency chain currently visible is therefore:

**MDE fundamentals → Model/Metamodel → EMF/Ecore → DSL/Xtext → Requirements modeling → Concern 1 → Use Cases → Concern 2**

---

# 6. Recommended starting concept

### **Model vs Metamodel**

This is the best starting point because the first concrete implementation work asks you to **extend a Metamodel and DSL**.

If this distinction is weak, the instruction:

> "Extend the requirements Metamodel and DSL..."

will become mechanical Eclipse work rather than something you can reason about and defend.

Knowledge state currently: **Not tested**.

---

# 7. Recommended first task

### **Do first: establish/confirm the project problem/domain**

Source: `ramde01` + `ramde03`.

This is blocking because both assigned concerns eventually require:

> model the requirements **of your problem**

and then:

> model the use cases **of your problem**

The project domain must satisfy the constraints in Lecture 03. After that, the first implementation task is to **replicate the light-switch Requirements example**, before extending it.

Evidence that the first task is complete: you have one defined problem/domain that can plausibly satisfy the four explicit Lecture 03 constraints. No specific document/template for proposing it is specified in these PDFs.

---

## First question — Model vs Metamodel

Suppose you write a specific requirement:

> `REQ-01: The system shall enable or disable power delivery to the load based on user input.`

And separately you define that every `Requirement` can have things such as `status`, `priority`, `risk` and `author`.

**Which of those two is the _model_, and which belongs to the _metamodel_? Why?**
