#include<stdio.h>
#include<stdlib.h>
struct node
{
 int d;
 int c;
 struct node*p;
 struct node*r;
 struct node*l;
};
struct node*root=NULL;
struct node*bst(struct node*trav,struct node*temp)
{
 if(trav==NULL)
 return temp;
 if(temp->d<trav->d)
 {
  trav->l=bst(trav->l,temp);
  trav->l->p=trav;
 }
 else if(temp->d>trav->d)
 {
  trav->r=bst(trav->r,temp);
  trav->r=trav;
 }
 return trav;
}
void rightrotate(struct node*temp)
{
 struct node*left=temp->l;
 temp->l=left->r;
 if(temp->l)
 temp->l->p=temp;
 left->p=temp->p;
 if(!temp->p)
 root=left;
 else if(temp==temp->p->l)
 temp->p->l=left;
 else
 temp->p->r=left;
 left->r=temp;
 temp->p=left;
}
void leftrotate(struct node*temp)
{
 struct node*right=temp->r;
 temp->r=right->l;
 if(temp->r)
 temp->r->p=temp;
 right->p=temp->p;
 if(!temp->p)
 root=right;
 else if(temp==temp->p->l)
 temp->p->l=right;
 else
 temp->p->r=right;
 right->l=temp;
 temp->p=right;
}
void fixup(struct node*root,struct node*pt)
{
 struct node*parent_pt=NULL;
 struct node*grand_parent_pt=NULL;
 int t;
 while((pt!=root)&&(pt->c!=0)&&(pt->p->c==1))
 {
  parent_pt=pt->p;
  grand_parent_pt=pt->p->p;
  if(parent_pt==grand_parent_pt->l)
  {
   struct node*uncle_pt=grand_parent_pt->r;
   if(uncle_pt!=NULL&&uncle_pt->c==1)
   {
    grand_parent_pt->c=1;
    parent_pt->c=0;
    uncle_pt->c=0;
    pt=grand_parent_pt;
   }
   else
   {
    if(pt==parent_pt->r)
    {
     leftrotate(parent_pt);
     pt=parent_pt;
     parent_pt=pt->p;
    }
    rightrotate(grand_parent_pt);
    t=parent_pt->c;
    parent_pt->c=grand_parent_pt->c;
    grand_parent_pt->c=t;
    pt=parent_pt;
   }
  }
  else
  {
   struct node*uncle_pt=grand_parent_pt->l;
   if((uncle_pt!=NULL)&&(uncle_pt->c==1))
   {
    grand_parent_pt->c=1;
    parent_pt->c=0;
    uncle_pt->c=0;
    pt=grand_parent_pt;
   }
   else
   {
    if(pt==parent_pt->l)
    {
     rightrotate(parent_pt);
     pt=parent_pt;
     parent_pt=pt->p;
    }
    leftrotate(grand_parent_pt);
    t=parent_pt->c;
    parent_pt->c=grand_parent_pt->c;
    grand_parent_pt->c=t;
    pt=parent_pt;
   }
  }
 }
 root->c=0;
}
void inorder(struct node*trav)
{
 if(trav==NULL)
 return;
 inorder(trav->l);
 printf("%d",trav->d);
 if(trav->c==0)
 printf("BLACK\t");
 else
 printf("RED\t");
 inorder(trav->r);
}
int main()
{
 int n=7;
 int i;
 int a[7]={7,6,5,4,3,2,1};
 clrscr();
 for(i=0;i<n;i++)
 {
  struct node*temp=(struct node*)malloc(sizeof(struct node));
  temp->r=NULL;
  temp->l=NULL;
  temp->p=NULL;
  temp->d=a[i];
  printf("%d",temp->d);
  temp->c=1;
  root=bst(root,temp);
  fixup(root,temp);
 }
 printf("Inorder traversal of created tree\n");
 inorder(root);
 getch();
 return 0;
}
