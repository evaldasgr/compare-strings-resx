# compare-strings-resx
compare-strings-resx is a simple utility that compares two ResX string files, and finds missing entries. It is useful in updating software translations, when new strings are added.

# Usage
The utility accepts two ResX files and prints out data names that are present in the first file, but are missing in the second. For example, to find entries that are in "File1.resx", but not in "File2.resx", run the following command:
```sh
$ compare-strings-resx File1.resx File2.resx
```

# Limitations
compare-strings-resx expects to find the <data> tag and it's attribute "name" on the same line. Additionally, it is required that the "name" attribute is the first, and is only separated from the tag by one space. For example, the following syntax will not be parsed correctly by the utility:
```xml
<data
name="Example">
<data foo="bar" name="Example">
<data  name="Example">
```
These issues will be addressed in future updates.
