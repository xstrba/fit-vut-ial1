# fit-vut-ial1
Repository with first project to course IAL.

#### All of this commands ur run from root directory of project:
##### compile and run basuc tests of all sub-projects:
```
$ make test
```

##### compile and run basic test of specific sub-project:
`$ make t_c202` or `$ make t_c204` or `$ make t_c206`

##### compile, run basic tests and compare with basic outputs for all sub-projects:
```
$ make compare
```

##### compile, run basic test and compare with basic output for specific sub-project:
`$ make cmp_c202` or `$ make cmp_c204` or `$ make cmp_c206`

###### If compare runs successfully - means that no differences are found between output of your test and sample outputs - you sould see lines like this on stdout: 

```
Beginning of [PROJECT NAME] diff
End of [PROJECT NAME] diff
```

###### Where [PROJECT NAME] is `c202` or `c204` or `c206`.

###### If there is something between this two lines, your test output doesn't match sample output.
