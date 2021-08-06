using namespace std;

vector<float> allCosines;

typedef map<string, int> DocMap;
typedef map<string, int> QueryMap;
typedef map<string, float> Similarity;



float Doc_mod(DocMap w)
{ float store=0;
  for (DocMap::iterator p = w.begin(); p != w.end(); ++p)
	store+=(p->second*p->second);
  return sqrt(store);
}

void map_sim(string x, float c, Similarity& sim)
{ sim[x]=c;
}

void cosineSimilarity(QueryMap q_obj, DocMap w, string x, Similarity &sim)
{ float c=(findTheDot(q_obj,w)/(Q_mod(q_obj)*Doc_mod(w)));
  //Similarity sim;
  map_sim(x,c, sim);
  allCosines.push_back(c);
}

//plan de negocios con las ultimas partes

int main()
{ DIR *pDIR;
  int i=0;
  struct dirent *entry;
  string x,y,folder_path, query_path;
  Similarity sim;
  QueryMap q_obj;

  cout<<"\nEnter folder path:";
  cin>>folder_path;
  cout<<"\nEnter query file path:";
  cin>>query_path;

  ifstream query_in(query_path.c_str());
  if(query_in.is_open())
	  countWords(query_in, q_obj);
  else
	cout<<"\nQuery file could not be opened!";

  if( pDIR=opendir(folder_path.c_str()) )
	{ while(entry = readdir(pDIR))
		{  if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
			{ x=entry->d_name;
			  y=folder_path+"/"+x;
			  if (y[y.length()-1]!='~')
				{ ifstream in(y.c_str());
				  if(in.is_open())
					{ DocMap w;
				 	  countWords(in, w);
					  //cout<<"\n";
					  cosineSimilarity(q_obj, w,x, sim);
					}
				  else
					cout<<"\nFile could not be opened!";
				}
			}
		}
	  closedir(pDIR);
	}
  sort(allCosines.begin(), allCosines.end());
  reverse(allCosines.begin(), allCosines.end());	//descending
  for(vector<double>::size_type g=0; g<3; g++)
		{ for(Similarity::iterator t=sim.begin(); t!=sim.end(); t++)
			if (t->second==allCosines[g])
				cout<<t->first<<"\n";
		}
  char hold;
  cout<<"\nEnter Q to quit!";
  cin>>hold;
  return 0;
}