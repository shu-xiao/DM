
git clone git@github.com:syuvivida/DM.git DM

cd DM

git checkout v0.03

git remote add upstream git@github.com:syuvivida/DM.git


### For commit later
git add xxxx

git commit -m "remove lines"

git pull --rebase upstream v0.03

git push origin v0.03
