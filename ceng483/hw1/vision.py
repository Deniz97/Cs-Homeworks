import glob
import cv2
import numpy as np
import _pickle as pc
import os
from sklearn import cluster
import compute_map
import convert_for_eval

NUMBER_OF_IMAGES = 1491
to_write = {} #for logging purposes

SIFT_TYPE = "sift" # "sift" or "dense_sift"
DENSE_STEP_SIZE = 15 #step size for dense sift

_nfeatures = 0	#default 0
_nOctaveLayers = 3	#default 3,
_contrastThreshold = 0.04	#default 0.04,
_edgeThreshold = 10	#default 10
_sigma = 1.6	#default 1.6 


_init_size = 300 #3*batch_size
_n_init = 10 #default 10
_reassignment_ratio = 0.01 #default 0.01
_batch_size = 10000 #default 100

K_MEANS_K = 256 # You think this is const? Cause it certainly is not.

np.random.seed(7) #lol random

to_write["nfeatures"] = _nfeatures
to_write["OctaveLayers"] = _nOctaveLayers
to_write["contrastThreshold"] = _contrastThreshold
to_write["edgeThreshold"] = _edgeThreshold
to_write["sigma"] = _sigma
to_write["init_size"] = _init_size
to_write["n_init"] = _n_init
to_write["reassignment_ratio"] = _reassignment_ratio
to_write["batch_size"] = _batch_size
to_write["step-size"] = DENSE_STEP_SIZE

####### Does your editor supports this: ẖ̸̢̧̼̤̼̱͖͔̯̙͑̅͌̽̀͗̂̍̾͐͝e̶̪̠͕̮͋́͛̔̃̆́̍́͝l̷̢̧̝̣̯̓̉̀̾̆̉͋̍̾͜͠͠͝͝l̵̡̬̘̹̯̮̣̅̿̐̅̀͛̉̒̃̂̃̈͝͝ỏ̴̻̦̪͎͓̫͇̺̜͕̣̒̄̌̌͌̇̿͘͜͝
####### mine does, haha

####### joke aside, dont go below, you have been warned

def generate_random(a,b,percentage=0,default=-1,intmi=False):
	#returns default with a change of percentage
	if( np.random.ranf() > percentage ):
		retval= (b-a) * np.random.ranf() + a
	else:
		retval = default

	if(intmi==True):
		return int(retval)

	return retval

def default_parameters():
	global _nfeatures
	global _nOctaveLayers
	global _contrastThreshold
	global _edgeThreshold
	global _sigma
	global _batch_size
	global _init_size
	global _n_init
	global _reassignment_ratio
	global K_MEANS_K
	global DENSE_STEP_SIZE
	
	_nOctaveLayers = 3	#default 3,
	_batch_size = 100 #default 100
	_init_size = 3000 #3*batch_size
	_n_init = 10 #default 10
	_reassignment_ratio =  0.01 #default 0.01
	_contrastThreshold = 0.04	#default 0.04,
	_edgeThreshold = 10	#default 10
	_sigma = 1.6 #default 1.6 
	if SIFT_TYPE == "sift":
		K_MEANS_K = 128
	elif SIFT_TYPE=="dense_sift":
		DENSE_STEP_SIZE = 10 #default 10
		K_MEANS_K = 256
	else:
		print("unrecognized sift type")
		exit()
	
	global to_write
	to_write["nfeatures"] = _nfeatures
	to_write["OctaveLayers"] = _nOctaveLayers
	to_write["contrastThreshold"] = _contrastThreshold
	to_write["edgeThreshold"] = _edgeThreshold
	to_write["sigma"] = _sigma
	to_write["init_size"] = _init_size
	to_write["n_init"] = _n_init
	to_write["reassignment_ratio"] = _reassignment_ratio
	to_write["batch_size"] = _batch_size
	to_write["step-size"] = DENSE_STEP_SIZE

def good_paremeters():
	global _nfeatures
	global _nOctaveLayers
	global _contrastThreshold
	global _edgeThreshold
	global _sigma
	global _batch_size
	global _init_size
	global _n_init
	global _reassignment_ratio
	global K_MEANS_K
	global DENSE_STEP_SIZE
	
	_nOctaveLayers = 3	#default 3,
	_batch_size = 10000 #default 100
	_init_size = 30.000 #3*batch_size
	_n_init = 20 #default 10
	_reassignment_ratio =  0.1 #default 0.01
	if SIFT_TYPE == "sift":
		_contrastThreshold = 0.01	#default 0.04,
		_edgeThreshold = 13	#default 10
		_sigma = 0.95 #default 1.6 
		K_MEANS_K = 128
	elif SIFT_TYPE=="dense_sift":
		_contrastThreshold = 0#0.03	#default 0.04,
		_edgeThreshold = 0#11	#default 10
		_sigma = 1.4	#default 1.6 
		DENSE_STEP_SIZE = 15 #default 10
		K_MEANS_K = 256
	else:
		print("unrecognized sift type")
		exit()
	
	global to_write
	to_write["nfeatures"] = _nfeatures
	to_write["OctaveLayers"] = _nOctaveLayers
	to_write["contrastThreshold"] = _contrastThreshold
	to_write["edgeThreshold"] = _edgeThreshold
	to_write["sigma"] = _sigma
	to_write["init_size"] = _init_size
	to_write["n_init"] = _n_init
	to_write["reassignment_ratio"] = _reassignment_ratio
	to_write["batch_size"] = _batch_size
	to_write["step-size"] = DENSE_STEP_SIZE

def randomize_parameters():
	global _nfeatures
	_nfeatures = generate_random(500,10000,0.7,0,intmi=True)	#default 0
	global _nOctaveLayers
	_nOctaveLayers = generate_random(1,7,0.7,3,intmi=True)	#default 3,
	global _contrastThreshold
	_contrastThreshold = generate_random(0.01,0.1,0.7,0.04)	#default 0.04,
	global _edgeThreshold
	_edgeThreshold = generate_random(3,20,0.7,10)	#default 10
	global _sigma
	_sigma = generate_random(0.1,4)	#default 1.6 
	global _batch_size
	_batch_size = generate_random(100,500,0.3,100,intmi=True) #default 100
	global _init_size
	_init_size = 3*_batch_size #3*batch_size
	global _n_init
	_n_init = 10 #default 10
	global _reassignment_ratio
	_reassignment_ratio = generate_random(0.005,0.05) #default 0.01
	global DENSE_STEP_SIZE
	DENSE_STEP_SIZE = generate_random(8,20,0.2,10,intmi=True) #default 10
	
	global to_write
	to_write["nfeatures"] = _nfeatures
	to_write["OctaveLayers"] = _nOctaveLayers
	to_write["contrastThreshold"] = _contrastThreshold
	to_write["edgeThreshold"] = _edgeThreshold
	to_write["sigma"] = _sigma
	to_write["init_size"] = _init_size
	to_write["n_init"] = _n_init
	to_write["reassignment_ratio"] = _reassignment_ratio
	to_write["batch_size"] = _batch_size
	to_write["step-size"] = DENSE_STEP_SIZE

def log_results(save_to="k",log=True):
	
	global to_write
	to_write["K"] = K_MEANS_K
	#result_filenames = get_all_result_filenames()
	if SIFT_TYPE=="sift":
		result_filenames = ["result_"+str(K_MEANS_K)+".txt"	]
	elif SIFT_TYPE=="dense_sift":
		result_filenames = ["dense_result_"+str(K_MEANS_K)+".txt"	]


	name = "val_"+name
	convert_for_eval.mainn(["filler",name])
	converted_filename = "converted_"+name
	map_score = compute_map.mainn(["filer",converted_filename,"./src/validation_gt.dat"])



	if log==False:
		return
	with open("result_log_"+save_to+"_proper.txt","a") as filem:
		filem.write("Best Score : %f \n" % map_score )
		filem.write("Params : %s \n" % str(to_write) )
		filem.write("Used k : %d \n\n\n" % K_MEANS_K )




## This series of methods' returns were definite at some point
## Now their return value further edited at couple of places
## But usually is not
def get_feat_filename():
	if SIFT_TYPE=="sift":
			feat_filename = "features.p"
	elif SIFT_TYPE == "dense_sift":
		feat_filename = "dense_features.p"
	else:
		print("UNRECOGNIZED SIFT TYPE, aborting")
		exit()
	return feat_filename

def get_result_filename():
	if SIFT_TYPE=="sift":
			feat_filename = "result_"+str(K_MEANS_K)+".txt"
	elif SIFT_TYPE == "dense_sift":
		feat_filename = "dense_result_"+str(K_MEANS_K)+".txt"
	else:
		print("UNRECOGNIZED SIFT TYPE, aborting")
		exit()
	return feat_filename

def get_all_result_filenames():
	retval = [0]*10
	
	retval[0] = "result_32.txt"
	retval[1] = "result_64.txt"
	retval[2] = "result_128.txt"
	retval[3] = "result_256.txt"
	retval[4] = "result_512.txt"
	retval[5] = "dense_result_32.txt"
	retval[6] = "dense_result_64.txt"
	retval[7] = "dense_result_128.txt"
	retval[8] = "dense_result_256.txt"
	retval[9] = "dense_result_512.txt"

	return retval

def get_bof_filename():
	if SIFT_TYPE=="sift":
			feat_filename = "bof_"+str(K_MEANS_K)+".p"
	elif SIFT_TYPE == "dense_sift":
		feat_filename = "dense_bof_"+str(K_MEANS_K)+".p"

	else:
		print("UNRECOGNIZED SIFT TYPE, aborting")
		exit()
	return feat_filename

def get_centers_filename():
	if SIFT_TYPE=="sift":
			feat_filename = "centers_"+str(K_MEANS_K)+".p"
	elif SIFT_TYPE == "dense_sift":
		feat_filename = "dense_centers_"+str(K_MEANS_K)+".p"
	else:
		print("UNRECOGNIZED SIFT TYPE, aborting")
		exit()
	return feat_filename

def get_kmeans_filename():
	if SIFT_TYPE=="sift":
			feat_filename = "kmeans_"+str(K_MEANS_K)+".p"
	elif SIFT_TYPE == "dense_sift":
		feat_filename = "dense_kmeans_"+str(K_MEANS_K)+".p"
	else:
		print("UNRECOGNIZED SIFT TYPE, aborting")
		exit()
	return feat_filename

def get_image_names():
	return glob.glob("./dataset/*")

def eucledian(v1,v2):
	return np.linalg.norm(v1-v2)

def get_sifted_image_kp_pair(img):
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	sift = cv2.xfeatures2d.SIFT_create(nfeatures = _nfeatures, nOctaveLayers=_nOctaveLayers,\
							contrastThreshold=_contrastThreshold,edgeThreshold=_edgeThreshold,\
							sigma=_sigma)
	kp = sift.detect(gray,None)
	cv2.drawKeypoints(img,kp,img,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

	return (img,kp)

def extract_features(img,sift = None):
	
	if(sift is None):
		sift = cv2.xfeatures2d.SIFT_create(nfeatures = _nfeatures, nOctaveLayers=_nOctaveLayers,\
							contrastThreshold=_contrastThreshold,edgeThreshold=_edgeThreshold,\
							sigma=_sigma)

	if SIFT_TYPE=="sift":
		kp = sift.detect(img,None)
		if(len(kp) < 5 ):
			#print("Found an image with %d keypoints" % len(kp))
			kp = [cv2.KeyPoint(x, y, 100) for y in range(0, img.shape[0], 100) 
												for x in range(0, img.shape[1], 100)]
	elif SIFT_TYPE=="dense_sift":

		kp = [cv2.KeyPoint(x, y, DENSE_STEP_SIZE) for y in range(0, img.shape[0], DENSE_STEP_SIZE) 
											for x in range(0, img.shape[1], DENSE_STEP_SIZE)]
		
	else:
		print("UNRECOGNIZED SIFT TYPE, aborting")
		exit()


	vector = sift.compute(img,kp)
	vector = vector[-1]
	
	return vector

def update_feature_vectors():
	pic_names_array = get_image_names()
	
	feat_filename = get_feat_filename()
	number_of_features = 0

	with open(feat_filename,"wb") as feat_file:
		sift = cv2.xfeatures2d.SIFT_create(nfeatures = _nfeatures, nOctaveLayers=_nOctaveLayers,\
							contrastThreshold=_contrastThreshold,edgeThreshold=_edgeThreshold,\
							sigma=_sigma)
		for index,pic in enumerate(pic_names_array):
			#if(index%100==0):
			#	print("Feature extracted %d images" % index)
			curr_image_gray = cv2.imread(pic,0) #0=read image as gray
			features = extract_features(curr_image_gray,sift)
			number_of_features += features.shape[0]
			#features = list(features)
			#map(lambda x:list(x),features)
			pc.dump(features,feat_file)

	return number_of_features, pic_names_array


def load_all_features(num_feat,image_names=""):
	feat_filename = get_feat_filename()
	number_of_features = num_feat

	all_features = np.zeros(shape=(number_of_features,128))

	featur_count_per_image = []

	with open(feat_filename,"rb") as feat_file:
		index = 0
		while True:
			#if(index%1000==0):
			#	print("Loaded %d features" % index)
			try:
				current_pic_features = pc.load(feat_file)
			except EOFError:
				break
			featur_count_per_image.append(current_pic_features.shape[0])
			for feat in current_pic_features:
				all_features[index] = feat
				index+=1

	assert len(featur_count_per_image)==len(image_names)==1491,"Different counts"
	return all_features,featur_count_per_image

			
def kmeans_and_save_clusters(all_features,k=K_MEANS_K):

	kmeans = cluster.MiniBatchKMeans(n_clusters=K_MEANS_K,verbose=0,n_init=_n_init,\
				compute_labels=False,init_size=_init_size,reassignment_ratio=_reassignment_ratio,\
				batch_size=_batch_size)
	kmeans.fit(all_features)
	centers_filename = get_centers_filename()
	kmeans_filename = get_kmeans_filename()

	with open(centers_filename,"wb") as filem:
		pc.dump(kmeans.cluster_centers_,filem)

	with open(kmeans_filename,"wb") as filem:
		pc.dump(kmeans,filem)

	return kmeans.cluster_centers_

def kmeans_and_save_clusters_and_save_bofs(all_features,names,counts):
	"""
	_init_size = 300 #3*batch_size
	_n_init = 10 #default 10
	_reassignment_ratio = 0.01 #default 0.01
	_batch_size = 100 #default 100
	"""

	kmeans = cluster.MiniBatchKMeans(n_clusters=K_MEANS_K,verbose=0,n_init=_n_init,\
				compute_labels=True,reassignment_ratio=_reassignment_ratio,\
				batch_size=_batch_size)
	kmeans.fit(all_features)
	print("Done k means")
	centers_filename = get_centers_filename()
	kmeans_filename = get_kmeans_filename()
	labels = kmeans.labels_

	with open(centers_filename,"wb") as filem:
		pc.dump(kmeans.cluster_centers_,filem)

	with open(kmeans_filename,"wb") as filem:
		pc.dump(kmeans,filem)

	pic_names_array = get_image_names()
	bof_filename = get_bof_filename()
	number_of_clusters = kmeans.cluster_centers_.shape[0]
	with open(bof_filename,"wb") as filem:
		to_write = []	
		curr_count = 0
		for img_index in range(len(counts)):
			#if(img_index%10==0):
			#	print("Bof featured %d image" %img_index)
			
			temp = labels[curr_count:curr_count+counts[img_index]].astype(np.float32)
			bof_vector = np.histogram(temp, bins=np.arange(number_of_clusters+1),density=True)[0]
			curr_count+=counts[img_index]
			####slice the image name
			img_name = names[img_index]
			img_name = img_name[img_name.rfind("/")+1:]
			###

			to_write.append((img_name,bof_vector))
		
		pc.dump(to_write,filem)


	return kmeans.cluster_centers_


def save_image_bof_pairs_using_kmeans():
	pic_names_array = get_image_names()

	kmeans_filename = get_kmeans_filename()
	bof_filename = get_bof_filename()

	with open(kmeans_filename,"rb") as filem:
		kmeans = pc.load(filem)
	number_of_clusters = kmeans.cluster_centers_.shape[0]
	sift = cv2.xfeatures2d.SIFT_create(nfeatures = _nfeatures, nOctaveLayers=_nOctaveLayers,\
							contrastThreshold=_contrastThreshold,edgeThreshold=_edgeThreshold,\
							sigma=_sigma)
	with open(bof_filename,"wb") as filem:
		to_write = []		
		for img_index,img_name in enumerate(pic_names_array):
			#if(img_index%10==0):
			#	print("Bof featured %d image" %img_index)
		
			curr_image_gray = cv2.imread(img_name,0) #0=read image as gray
			features = extract_features(curr_image_gray,sift)

			bof_vector = np.zeros((kmeans.cluster_centers_.shape[0],))
			if(features.shape[0]!=0):
				temp = kmeans.predict(features).astype(np.float32)
				bof_vector = np.histogram(temp, bins=np.arange(number_of_clusters+1),density=True)[0]
				
			else:
				bof_vector = np.zeros( (number_of_clusters ,))
			####slice the image name
			img_name = img_name[img_name.rfind("/")+1:]
			###

			to_write.append((img_name,bof_vector))
		
		pc.dump(to_write,filem)


def get_similiar_images(img_name,all_bof_vectors = None):

	if all_bof_vectors is None:
		bof_filename = get_bof_filename()

		with open(bof_filename,"rb") as filem:
			all_bof_vectors = pc.load(filem)
		
	####check if image bof already computed
	filtered_bof = list(filter(lambda x:img_name in x[0],all_bof_vectors))
	if len(filtered_bof)==1:
		current_bof_vector = filtered_bof[0][1]
	elif len(filtered_bof) > 0:
		print("What? PROBLEM IN GET SIMILIAR IMAGES")
	else:
		kmeans_filename = get_kmeans_filename()
		bof_filename = get_bof_filename()

		curr_image_gray = cv2.imread(img_name,0) #0=read image as gray
		features = extract_features(curr_image_gray)

		with open(kmeans_filename,"rb") as filem:
			kmeans = pc.load(filem)
			if(features.shape[0]!=0):
				current_bof_vector = kmeans.predict(features).astype(np.float32)
				#normalize
				current_bof_vector /= features.shape[0]
			else:
				current_bof_vector = np.zeros((kmeans.cluster_centers_.shape[0],))

	####

	distance_array = np.zeros(shape=(NUMBER_OF_IMAGES,))
	image_names_array = [0]*(NUMBER_OF_IMAGES)
	for index,bof in enumerate(all_bof_vectors):
		#current_bof_vector *= 100
		#bof_values = bof[1] * 100
		
		distance_array[index] = eucledian(current_bof_vector,bof[1])
		image_names_array[index] = bof[0]
	

	return list(zip(distance_array,image_names_array))


def query_validation_set():
	validation_file = "validation_queries.dat"
	result_filename = "val_"+get_result_filename()
	bof_filename = get_bof_filename()

	with open(bof_filename,"rb") as bof_file:
		all_bof_vectors = pc.load(bof_file)

	with open(result_filename,"w") as res_file:
		for line in open(validation_file,"r"):
			curr_val_image_name = line.rstrip('\n')
			query_result = get_similiar_images(curr_val_image_name,all_bof_vectors)
			query_result = list( map(lambda x:str(x[0])+" "+str(x[1]),query_result) )
			query_string =" ".join(query_result)
			res_file.write(curr_val_image_name+": "+query_string+'\n')

def query_test_set():
	test_file = "test_queries.dat"
	result_filename = "test_"+get_result_filename()
	bof_filename = get_bof_filename()

	with open(bof_filename,"rb") as bof_file:
		all_bof_vectors = pc.load(bof_file)

	with open(result_filename,"w") as res_file:
		for line in open(test_file,"r"):
			curr_val_image_name = line.rstrip('\n')
			query_result = get_similiar_images(curr_val_image_name,all_bof_vectors)
			query_result = list( map(lambda x:str(x[0])+" "+str(x[1]),query_result) )
			query_string =" ".join(query_result)
			res_file.write(curr_val_image_name+": "+query_string+'\n')

	
def full_pipeline(k=-1,q_type="val"):

	global K_MEANS_K
	global to_write

	if k>0:
		K_MEANS_K = k
	print("K= ",K_MEANS_K)
	image_names = get_image_names()
	
	total_feature_count,image_names = update_feature_vectors()

	if SIFT_TYPE=="sift":
		to_write["total_feature_count-sift"] = total_feature_count
	elif SIFT_TYPE=="dense_sift":
		to_write["total_feature_count-dense"] = total_feature_count

	print("Total feature : ",total_feature_count)

	
	all_features, feat_counts = load_all_features(total_feature_count,image_names)
	print("All feature shape : ",all_features.shape)
	
	clusters = kmeans_and_save_clusters_and_save_bofs(all_features, image_names,feat_counts)
	print("Saved bof_pairs, Cluster shape : ",clusters.shape)
	
	if q_type=="val":
		query_validation_set()
		print("Queried and saved validation set")
	elif q_type=="test":
		query_test_set()
		print("Queried and saved test set")
	print()


def iterate_all_k_values():
	full_pipeline(32)
	full_pipeline(64)
	full_pipeline(128)
	full_pipeline(256)
	full_pipeline(512)

def go_full_blown_crazy():
	global to_write
	global SIFT_TYPE
	while True:
		try:
			SIFT_TYPE = "sift"
			randomize_parameters()
			print("Working for: ")
			print(str(to_write))
			print()
			full_pipeline(256)
			print("Finished, logging")
			"""
			print("Finished for normal sift, starting for dense")
			SIFT_TYPE = "dense_sift"
			full_pipeline(256)
			print("Finished dense too,logging")
			"""
			log_results()
			print()
			print()
		except MemoryError:
			print("Memory Error, continuing:")
			print()
			print()
			continue

def search_k():
	global to_write
	global SIFT_TYPE
	global _sigma
	SIFT_TYPE = "sift"
	for k in [80,90,100,110,140,150,160,170,200]:
		try:
			
			print("Working for k: %d" % k)
			print(str(to_write))
			print()
			full_pipeline(k)
			print("Finished, logging")
			log_results(k)
			print()
			print()
		except MemoryError:
			print("Memory Error, continuing:")
			print()
			print()
			continue


def search_sigma():
	global to_write
	global SIFT_TYPE
	global _sigma
	SIFT_TYPE = "sift"
	for sigma in [0.1,0.3,0.5,0.7,0.9,1,1.2,1.4,1.7,2,2.4,2.8,3.2,3.7,4,4.5,5]:
		try:
			_sigma = sigma
			to_write["sigma"] = _sigma
			print("Working for k: %d" % 256)
			print(str(to_write))
			print()
			full_pipeline(128)
			print("Finished, logging")
			log_results(128)
			print()
			print()
		except MemoryError:
			print("Memory Error, continuing:")
			print()
			print()
			continue

def search_et():
	global to_write
	global SIFT_TYPE
	global _edgeThreshold
	SIFT_TYPE = "dense_sift"
	for et in np.linspace(8,19,15):
		try:
			_edgeThreshold = et
			to_write["edgeThreshold"] = _edgeThreshold
			print("Working for k: %d" % 256)
			print("Working for et: %d" % _edgeThreshold)
			print(str(to_write))
			print()
			full_pipeline(256)
			print("Finished, logging")
			log_results(256)
			print()
			print()
		except MemoryError:
			print("Memory Error, continuing:")
			print()
			print()
			continue
	
def search_ct():
	global to_write
	global SIFT_TYPE
	global _contrastThreshold
	SIFT_TYPE = "sift"
	for ct in np.linspace(0.01,0.1,15):
		try:
			_contrastThreshold = ct
			to_write["contrastThreshold"] = _contrastThreshold
			print("Working for k: %d" % 128)
			print("Working for ct: %d" % _contrastThreshold)
			print(str(to_write))
			print()
			full_pipeline(128)
			print("Finished, logging")
			log_results(128)
			print()
			print()
		except MemoryError:
			print("Memory Error, continuing:")
			print()
			print()
			continue

def search_ss():
	global to_write
	global SIFT_TYPE
	global DENSE_STEP_SIZE
	SIFT_TYPE = "dense_sift"
	for ss in [3,4,5,6,7,8,9,10,11,13,15,18,22,26,35,45,60,90,110]:
		try:
			DENSE_STEP_SIZE = ss
			to_write["step-size"] = ss
			print("Working for k: %d" % 256)
			print("Working for ss: %d" % ss)
			print(str(to_write))
			print()
			full_pipeline(256)
			print("Finished, logging")
			log_results(256)
			print()
			print()
		except MemoryError:
			print("Memory Error, continuing:")
			print()
			print()
			continue
	

def give_best_results(s_type="dense_sift",q_type="test",k=-1):
	assert q_type=="test" or q_type=="val","Wrong q_type"
	assert s_type=="sift" or s_type=="dense_sift","Wrong s_type"

	global SIFT_TYPE
	SIFT_TYPE = s_type

	good_paremeters()

	if k>0:
		global K_MEANS_K
		K_MEANS_K = k


	full_pipeline(k,q_type)



if __name__ == '__main__':
	give_best_results("dense_sift","val")
	#search_ct()
	#go_full_blown_crazy()
	#query_validation_set()
	#all_features = update_feature_vectors()
	#total_features = load_all_features()
