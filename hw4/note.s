char newKey[26];
int seenArray[26];

//initialize all slots of seenArray to 0;

int currentNewKeyIdx = 0;
int i=0;
for each character in key:
  char c = key[i];
  int seenIdx = c - 97;
  if (seenArray[seenIdx] == 0) {
    newKey[currentNewKeyIdx] = c;
    currentNewKeyIdx++;
    seenArray[seenIdx] = 1;
  }
  i++;
}

//tack on the remaining unseen characters.

//copy each index from newKey over to oldKey
for int i = 0; i < 26; i++ {
  key[i] = newKey[i]
}
