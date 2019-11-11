
import random
import matplotlib.pyplot as plt
class PageReplace(object):
	def __init__(self):
		self.frame_seq = []
		self.frame_num = 0
		self.page_size = 0
		self.hit = 0
		self.miss = 0
		self.page_mem = []
		self.total_ref = 0
		self.gen_data()

	def gen_data(self):
		self.frame_num = int(random.random()*100)
		
		for i in range(self.frame_num):
			self.frame_seq.append(int(random.random()*100))
		
	def reset_data(self):
		self.hit = 0
		self.miss = 0
		self.total_ref = 0
		self.page_mem = []


	def LRU(self):
		self.reset_data()
		
		for frame in self.frame_seq:
			if frame in self.page_mem:
				index = self.page_mem.index(frame)
				del self.page_mem[index]
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.hit += 1
			elif len(self.page_mem)<self.page_size:
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.miss += 1
			elif len(self.page_mem)>=self.page_size:
				del self.page_mem[len(self.page_mem)-1]
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.miss += 1
			

	def FIFO(self):
		self.reset_data()
		
		for frame in self.frame_seq:
			if frame in self.page_mem:
				self.total_ref += 1
				self.hit += 1
			elif len(self.page_mem)<self.page_size:
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.miss += 1
			else:
				del self.page_mem[len(self.page_mem)-1]
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.miss += 1
			
	def LFU(self):
		self.reset_data()
		
		for frame in self.frame_seq:
			flag = 0
			for page in self.page_mem:
				if page[0]== frame:
					self.page_mem[self.page_mem.index(page)][1]+= 1
					flag = 1
					self.total_ref += 1
					self.hit += 1
					break
			if flag == 0:
				if len(self.page_mem) < self.page_size:
					self.page_mem.insert(0,[frame,1])
					self.total_ref += 1
					self.miss += 1
				else:
					minpage = [10e9,10e9]
					for page in self.page_mem:
						if minpage[1] > page[1]:
							minpage = page
					del self.page_mem[self.page_mem.index(minpage)]
					self.page_mem.insert(0,[frame,1])
					self.total_ref += 1
					self.miss += 1
			

	def RDM(self):
		self.reset_data()
		
		for frame in self.frame_seq:
			if frame in self.page_mem:
				self.total_ref += 1
				self.hit += 1
			elif len(self.page_mem)<self.page_size:
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.miss += 1
			else:
				del self.page_mem[(int(random.random()*10))%self.page_size]
				self.page_mem.insert(0, frame)
				self.total_ref += 1
				self.miss += 1
			
	
	def ALRU(self):
		self.reset_data()
		
		for frame in self.frame_seq:
			flag = 0
			for page in self.page_mem:
				if page[0] == frame:
					page[1] = 1
					self.hit += 1
					self.total_ref += 1
					flag = 1
					break
			if flag == 0:
				if len(self.page_mem)<self.page_size:
					self.page_mem.insert(0, [frame,0])
					self.total_ref += 1
					self.miss += 1
				else:
					el = self.page_mem[0]
					jflag = 0
					for pos,page in enumerate(self.page_mem):
						if page[1] == 0:
							for ipos,ipage in enumerate(self.page_mem[pos:]):
								if ipage[1] == 1:
									for jpos,jpage in enumerate(self.page_mem[ipos:]):
										if jpage[1] == 0:
											jflag = 1
											el = jpage
											break
									if jflag == 0:
										for jpos,jpage in enumerate(self.page_mem):
											if jpage[1] == 0:
												jflag = 1
												el = jpage
												break
								if jflag:
									break
						if jflag:
							break
					
					del self.page_mem[self.page_mem.index(el)]
					self.page_mem.insert(0, [frame,0])
					self.total_ref += 1
					self.miss += 1
			

if __name__ == '__main__':
	pageObj = PageReplace()
	pagesizelist = [i for i in range(1,101)]
	hitratiolist_lru = []
	hitratiolist_alru = []
	hitratiolist_fifo = []
	hitratiolist_rdm = []
	
	hitratiolist_lfu = []

	print('Frame Sequence :\n',pageObj.frame_seq)
	for i in range(1,101):
		pageObj.page_size = i
		pageObj.LRU()
		hitratiolist_lru.append(pageObj.hit)
		pageObj.ALRU()
		hitratiolist_alru.append(pageObj.hit)
		pageObj.FIFO()
		hitratiolist_fifo.append(pageObj.hit)
		pageObj.LFU()
		hitratiolist_lfu.append(pageObj.hit)
		pageObj.RDM()
		hitratiolist_rdm.append(pageObj.hit)
		
	# print(pagesizelist)
	plt.xlabel('Page Size')
	plt.ylabel('Page Hit')
	plt.plot(pagesizelist,hitratiolist_lru,c='r',label='LRU')
	plt.plot(pagesizelist,hitratiolist_alru,c='g',label='ALRU')
	plt.plot(pagesizelist,hitratiolist_fifo,c='b',label='FIFO')
	plt.plot(pagesizelist,hitratiolist_lfu,c='c',label='LFU')
	plt.plot(pagesizelist,hitratiolist_rdm,c='k',label='RDM')
	
	plt.legend()
	plt.show()
	# print(hitratiolist_lru)

